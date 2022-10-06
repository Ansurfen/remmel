#ifndef __REMMEL_MLSM_SSTABLE__
#define __REMMEL_MLSM_SSTABLE__

#include "../../lib/cast.hpp"
#include "../../lib/debug.hpp"
#include "../../lib/io.hpp"
#include "memtable.hpp"

namespace remmel
{
    struct TableMetaInfo
    {
        uint64_t dataStart;
        uint64_t dataLen;
        uint64_t indexStart;
        uint64_t indexLen;
        uint64_t size;
        TableMetaInfo();
        void read(Ifstream *);
        void write(Ofstream *);
        FStr toString();
    };

    class SsTable
    {
    private:
        TableMetaInfo meta;
        Ofstream *ofp; // require a file engine
        Ifstream *ifp;
        MemTable memtable;
        Str in;

    public:
        SsTable();
        SsTable(FStr);
        ~SsTable();
        void write(FStr);
        void read(FStr);
        uint32_t query(FStr);
        FStr get(uint32_t);
    };
}

#endif