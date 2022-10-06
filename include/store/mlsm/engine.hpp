#ifndef __REMMEL_MLSM__
#define __REMMEL_MLSM__

#include "sstable.hpp"
#include "../../lib/io.hpp"

namespace remmel
{
    struct MLSM_Record
    {
        char boundary[8];
        uint32_t late;
        char filename[12];
    };

    union MLSM_Record_toString
    {
        struct MLSM_Record val;
        char buf[sizeof(MLSM_Record)];
        MLSM_Record_toString(MLSM_Record _val) : val(_val) {}
    };
    // split namespace
    class MLSMStore
    {
    private:
        HashMap<FStr, SsTable> sstables;
        // metas
        Str in;
        uint32_t letter[26];
        uint32_t count;
        Ofstream *ofp;

        void writeRecord(FStr, FStr);

    public:
        MLSMStore(FStr);
        ~MLSMStore();
        void Open(FStr); // open index file
        void Query(FStr);
    };
}

#endif