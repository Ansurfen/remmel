#ifndef __REMMEL_CALL_STACK__
#define __REMMEL_CALL_STACK__

#include "../lib/constant.hpp"
#include "../lib/mem.hpp"

namespace remmel
{
    class CallStack
    {
    private:
        Stack<void *> master, slave;
        Stack<int> mbps, sbps; // breakpoints

    public:
        CallStack();
        ~CallStack();
        void *operator new(size_t);
        void operator delete(void *);
        void push(void *);
        void pop();
        int size() const;
        void save();
        bool roll(); // from master to slave
        bool pour(); // from slave to master
    };

    MemPool<sizeof(CallStack), 4> cs_poll;
}

#endif