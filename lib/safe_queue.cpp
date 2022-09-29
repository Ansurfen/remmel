#include "../include/lib/safe_queue.hpp"

using namespace remmel;

template <class T>
remmel::safe_queue<T>::safe_queue() {}

template <class T>
remmel::safe_queue<T>::~safe_queue() {}

template <class T>
void safe_queue<T>::push(T data)
{
    UniLock<Mutex> lock(this->mut);
    this->datas.push(T);
}

template <class T>
void remmel::safe_queue<T>::pop()
{
    UniLock<Mutex> lock(this->mut);
    this->datas.pop();
}

template <class T>
T remmel::safe_queue<T>::get()
{
    UniLock<Mutex> lock(this->mut);
    T front = this->datas.front();
    this->datas.pop();
    return front;
}

template <class T>
T remmel::safe_queue<T>::front()
{
    UniLock<Mutex> lock(this->mut);
    return this->datas.front();
}

template <class T>
int remmel::safe_queue<T>::size() const
{
    UniLock<Mutex> lock(this->mut);
    return this->datas.size();
}