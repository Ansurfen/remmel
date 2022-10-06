#ifndef __REMMEL_STORE__
#define __REMMEL_STORE__

#include "mlsm/engine.hpp"
#include "../lib/crypto.hpp"
#include "../lib/bitarray.hpp"

namespace remmel
{
    typedef struct
    {
        uint8_t boundary;
        BitArray mask;
        BitArray path;
    } IndexMeta;

    class Store
    {
    private:
#ifdef __REMMEL_MLSM__
        Map<FStr, MLSMStore *> *instance;
#endif
    public:
        Store();
        ~Store();
        void init(uint8_t, ...);
        void open(FStr, FStr);
        FStr get(FStr, FStr);
    };
}

#endif