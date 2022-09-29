#ifndef __REMMEL_HEAP__
#define __REMMEL_HEAP__

#include "constant.hpp"

namespace remmel
{
    template <typename T,
              typename sequence = Vec<T>,
              unsigned const int n = 2,
              typename compare = std::less<T>>
    class heap
    {
    protected:
        sequence datas;
        compare cmp;

        void up(uint32_t);
        void down(uint32_t);

    public:
        heap();
        heap(const Vec<T> &);
        heap(const Deque<T> &);
        ~heap();
        void push(const T &);
        void pop();
        const T &top() const;
        const uint32_t size() const;
        const bool empty() const;
    };
}

#endif