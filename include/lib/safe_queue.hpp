#ifndef __REMMEL_SAFE_QUEUE__
#define __REMMEL_SAFE_QUEUE__

#include "constant.hpp"

namespace remmel
{
    template <typename T>
    class safe_queue
    {
    private:
        Mutex mut;
        Que<T> datas;

    public:
        safe_queue();
        ~safe_queue();
        void push(T);
        void pop();
        T get();
        T front();
        int size() const;
    };
}

#endif