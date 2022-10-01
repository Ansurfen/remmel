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
        void unsafe_push(T);
        void pop();
        void unsafe_pop();
        T get();
        T unsafe_get();
        T front();
        T unsafe_front();
        int size() const;
        int unsafe_size() const;
        bool empty() const;
        bool unsafe_empty() const;
    };
}

#endif