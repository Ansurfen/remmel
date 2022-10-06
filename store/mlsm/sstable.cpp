#include "../../include/store/mlsm/sstable.hpp"

using namespace remmel;

TableMetaInfo::TableMetaInfo() {}

void TableMetaInfo::write(Ofstream *fp)
{
#define writeUint64(val)     \
    temp = _llong2bit_(val); \
    fp->write((CStr)temp.buf, LLONG_LEN)

    REM_LLONG temp;
    writeUint64(this->dataStart);
    writeUint64(this->dataLen);
    writeUint64(this->indexStart);
    writeUint64(this->indexLen);
    writeUint64(this->size);
}

void TableMetaInfo::read(Ifstream *fp)
{
#define readUint64(offset, member)                \
    fp->seekg(-LLONG_LEN *offset, std::ios::end); \
    fp->read((char *)temp.buf, LLONG_LEN);        \
    this->##member = temp.val

    fp->seekg(0, std::ios::end);
    uint64_t len = fp->tellg();
    REM_LLONG temp;
    readUint64(1, size);
    readUint64(2, indexLen);
    readUint64(3, indexStart);
    readUint64(4, dataLen);
    readUint64(5, dataStart);
}

SsTable::SsTable(FStr path)
{
    this->in = ReadFile(path.data());
}

void SsTable::write(FStr path)
{
    this->ofp->open(path.data());
    Str dataPart;
    Str indexPart;
    REM_LLONG start;
    start.val = 0;
    for (FStr k : this->memtable.toString(true))
    {
        FStr v = this->memtable.Get(k);
        dataPart += k.data();
        dataPart += v.data();
        REM_LONG boundary;
        REM_LLONG len;
        boundary.val = k.size();
        len.val = k.size() + v.size();
        indexPart += (CStr)start.buf;
        indexPart += (CStr)boundary.buf;
        indexPart += (CStr)len.buf;
        start.val += k.size() + v.size();
    }
    *this->ofp << dataPart << indexPart;
    this->meta.write(this->ofp);
}

void SsTable::read(FStr path)
{
    this->ifp->open(path.data());
    if (!this->ifp->is_open())
    {
        WARN("fail to open the file");
        return;
    }
    this->meta.read(this->ifp);
    char ch;
    while ((ch = this->ifp->get()) != EOF)
        this->in += ch;
}

uint32_t SsTable::query(FStr name)
{
#define GetKeyStart(index) std::atoll(index.substr(0, 8).data())
#define GetKeyLen(index) std::atoll(index.substr(8, 4).data())
#define GetKey(index) this->in.substr(GetKeyStart(index), GetKeyLen(index))

    uint8_t indexSize = LLONG_LEN * 2 + LONG_LEN;
    uint64_t start = this->meta.indexStart;
    uint32_t cnt = this->meta.indexLen / indexSize;
    // start(8 bit) | boundary(4bit) | len(8bit)
    // boundary = key length, len - boundary = value length
    FStr startindex = this->in.substr(start, indexSize);
    FStr endindex = this->in.substr(start + (cnt - 1) * indexSize, indexSize);
    if (GetKey(startindex) > name && name > GetKey(endindex))
        return -1;
    uint32_t i;
    for (i = 0; i <= cnt / 2; i++)
    {
        startindex = this->in.substr(i, indexSize);
        endindex = this->in.substr((cnt - i) * indexSize, indexSize);
        if (GetKey(startindex) <= name && name <= GetKey(endindex))
            continue;
        else
            return -1;
    }
    return startindex == name ? i : cnt - i;
}

SsTable::~SsTable()
{
    this->ifp->close();
    this->ofp->close();
    delete this->ifp;
    delete this->ofp;
}