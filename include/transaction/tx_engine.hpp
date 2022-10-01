#ifndef __REMMEL_TX_ENGINE__
#define __REMMEL_TX_ENGINE__

#include "locks.hpp"
#include "call_stack.hpp"

namespace remmel
{
#define GetTxEngine TxEngine::get_engine()

    class TxEngine
    {
    private:
        static TxEngine *instance;
        TxLocks *locks;
        Vec<CallStack *> callstacks;

    public:
        TxEngine();
        ~TxEngine();
        static TxEngine *get_engine();
        uint32_t begin();   // get transaction descriptor
        void end(uint32_t); // free transaction descriptor
        void save(uint32_t);
        void push(uint32_t, void *);
        void pop(uint32_t);
        bool roll(uint32_t);
        bool pour(uint32_t);
        void alloc();
        void free(uint32_t);
        // get data from rollback
        void *get(uint32_t);
    };

    TxEngine *TxEngine::instance = nullptr;
}

#endif