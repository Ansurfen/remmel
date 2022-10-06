#include "../../include/store/mlsm/engine.hpp"

using namespace remmel;

MLSMStore::MLSMStore(FStr path)
{
    Ifstream fp(path.data());
    for (uint8_t i = 0; i < 26; i++)
        this->letter[i] = NIL;
}

void MLSMStore::Query(FStr name)
{
    uint64_t len = this->in[this->in.length()];
    uint8_t offset = sizeof(MLSM_Record);
    uint32_t pos = this->letter[name[0] - 'a'];
    for (;;)
    {
        Str s = this->in.substr(pos, offset);
        if (s.substr(0, 4) <= name && name <= s.substr(4, 4))
        {
            FStr in = ReadFile(s.substr(12, 12));
            SsTable sstable(in);
            uint32_t res;
            if (!(res = sstable.query(name))) // require to implement cache
                pos = std::atol(s.substr(8, 4).data());
            else
            {
                FStr result = sstable.get(res);
            }
        }
        else
            pos = std::atol(s.substr(8, 4).data());
    }
}

void MLSMStore::writeRecord(FStr up, FStr down)
{
    MLSM_Record record;
    record.late = this->letter[up[0] - 'a'];
    char ch = 0;
    for (uint8_t i = 0; i < 8; i++)
    {
        if (i < 4)
        {
            if (up.size() <= i)
                ch = 0;
            else
                ch = up[i];
        }
        else
        {
            if (down.size() <= i - 4)
                ch = 0;
            else
                ch = down[i - 4];
        }
        record.boundary[i] = ch;
    }
    *this->ofp << MLSM_Record_toString(record).buf;
    this->letter[up[0] - 'a'] = this->count;
    this->count++;
}