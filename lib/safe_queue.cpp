#include "../include/lib/safe_queue.hpp"

using namespace remmel;

template <class T>
safe_queue<T>::safe_queue() {}

template <class T>
safe_queue<T>::~safe_queue() {}

template <class T>
void safe_queue<T>::push(T data)
{
    UniLock<Mutex> lock(this->mut);
    this->datas.push(data);
}

template <class T>
void safe_queue<T>::unsafe_push(T data)
{
    this->datas.push(data);
}

template <class T>
void safe_queue<T>::pop()
{
    UniLock<Mutex> lock(this->mut);
    if (this->unsafe_empty())
        return;
    this->datas.pop();
}

template <class T>
void safe_queue<T>::unsafe_pop()
{
    if (this->unsafe_empty())
        return;
    this->datas.pop();
}

template <class T>
T safe_queue<T>::get()
{
    UniLock<Mutex> lock(this->mut);
    if (this->unsafe_empty())
        return (T)-1;
    T front = this->datas.front();
    this->datas.pop();
    return front;
}

template <class T>
T safe_queue<T>::unsafe_get()
{
    if (this->unsafe_empty())
        return (T)-1;
    T front = this->datas.front();
    this->datas.pop();
    return front;
}

template <class T>
T safe_queue<T>::front()
{
    UniLock<Mutex> lock(this->mut);
    return this->datas.front();
}

template <class T>
T safe_queue<T>::unsafe_front()
{
    return this->datas.front();
}

template <class T>
int safe_queue<T>::size() const
{
    UniLock<Mutex> lock(this->mut);
    return this->datas.size();
}

template <class T>
int safe_queue<T>::unsafe_size() const
{
    return this->datas.size();
}

template <class T>
bool safe_queue<T>::empty() const
{
    UniLock<Mutex> lock(this->mut);
    return this->datas.empty();
}

template <class T>
bool safe_queue<T>::unsafe_empty() const
{
    return this->datas.empty();
}