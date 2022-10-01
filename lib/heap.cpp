#include "../include/lib/heap.hpp"

using namespace remmel;

template <class T, class sequence, const uint32_t n, class compare>
heap<T, sequence, n, compare>::heap()
{
}

template <class T, class sequence, const uint32_t n, class compare>
heap<T, sequence, n, compare>::heap(const Vec<T> &datas)
{
    for (const T &data : datas)
    {
        this->datas.emplace_back(data);
        this->up(this->datas.size() - 1);
    }
}

template <class T, class sequence, const uint32_t n, class compare>
heap<T, sequence, n, compare>::heap(const Deque<T> &datas)
{
    for (const T &data : datas)
    {
        this->datas.emplace_back(data);
        this->up(this->datas.size() - 1);
    }
}

template <class T, class sequence, const uint32_t n, class compare>
heap<T, sequence, n, compare>::~heap()
{
}

template <class T, class sequence, const uint32_t n, class compare>
void heap<T, sequence, n, compare>::up(uint32_t x)
{
    while (x)
    {
        uint32_t fi = (x - 1) / n; // father index
        if (this->cmp(datas[x], this->datas[fi]) == 0)
        {
            Swap(this->datas[x], this->datas[fi]);
            x = fi;
        }
        else
            break;
    }
}

template <class T, class sequence, const uint32_t n, class compare>
void heap<T, sequence, n, compare>::down(uint32_t x)
{
    while (x * n + 1 < this->datas.size())
    {
        uint32_t si = x * n + 1; // son index
        T tmp = this->datas[x * n + 1];
        for (uint32_t i = 2; i <= n && x * n + i < this->datas.size(); i++)
        {
            if (!this->cmp(this->datas[x * n + i], tmp))
            {
                tmp = this->datas[x * n + i];
                si = x * n + i;
            }
        }
        if (this->cmp(this->datas[x], this->datas[si]) == 1)
        {
            Swap(this->datas[x], this->datas[si]);
            x = si;
        }
        else
            break;
    }
}

template <class T, class sequence, const uint32_t n, class compare>
void heap<T, sequence, n, compare>::push(const T &data)
{
    this->datas.emplace_back(data);
    this->up(this->datas.size() - 1);
}

template <class T, class sequence, const uint32_t n, class compare>
void heap<T, sequence, n, compare>::pop()
{
    Swap(this->datas[0], this->datas[this->datas.size() - 1]);
    this->datas.pop_back();
    this->down(0);
}

template <class T, class sequence, const uint32_t n, class compare>
const T &heap<T, sequence, n, compare>::top() const
{
    return this->datas[0];
}

template <class T, class sequence, const uint32_t n, class compare>
const uint32_t heap<T, sequence, n, compare>::size() const
{
    return this->datas.size();
}

template <class T, class sequence, const unsigned int n, class compare>
const bool heap<T, sequence, n, compare>::empty() const
{
    return this->datas.empty();
}