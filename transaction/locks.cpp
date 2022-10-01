#include "../include/transaction/locks.hpp"

using namespace remmel;

TxLocks::TxLocks(uint32_t n)
{
    for (uint32_t i = 0; i < n; i++)
        this->locks.unsafe_push(i);
    this->cap = this->locks.unsafe_size();
    this->stw = false;
}

TxLocks::~TxLocks() {}

uint32_t TxLocks::get()
{
    if (this->stw)
        return -1;
    return this->locks.get();
}

void TxLocks::release(uint32_t lock)
{
    if (this->stw && lock == this->cap - 1)
    {
        this->set_stw();
        return;
    }
    this->locks.push(lock);
}

void TxLocks::add()
{
    this->locks.push(this->cap);
    this->cap++;
}

void TxLocks::del()
{
    this->set_stw();
}

void TxLocks::set_stw()
{
    this->stw = ~this->stw;
}

uint32_t TxLocks::get_cap() const
{
    return this->cap;
}