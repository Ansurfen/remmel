#ifndef __REMMEL_MLSM_MEMTABLE__
#define __REMMEL_MLSM_MEMTABLE__

#include "../../lib/tire.hpp"

namespace remmel
{
    class MemTable
    {
    private:
        TTire<FStr> *tire;
        Vec<FStr> words;

    public:
        MemTable();
        ~MemTable();
        void Insert(FStr, FStr);
        void Delete(FStr);
        FStr Get(FStr);
        Vec<FStr> toString(bool isSort = true);
    };
}

#endif