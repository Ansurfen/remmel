#ifndef __REMMEL_TX_LOCKS__
#define __REMMEL_TX_LOCKS__

#include "../lib/libr.hpp"
#include "../lib/safe_queue.hpp"

namespace remmel
{
    class TxLocks
    {
    private:
        safe_queue<uint32_t> locks;
        uint32_t cap;
        bool stw; // stop the world

    public:
        TxLocks(uint32_t);
        ~TxLocks();
        uint32_t get(); // if stw, return -1
        void release(uint32_t);
        void add();
        void del();
        void set_stw();
        uint32_t get_cap() const;
    };
}

#endif