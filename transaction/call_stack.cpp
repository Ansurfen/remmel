#include "../include/transaction/call_stack.hpp"

using namespace remmel;

CallStack::CallStack()
{
    this->mbps.push(0);
}

CallStack::~CallStack()
{
    while (this->master.size() || this->slave.size() || this->mbps.size() || this->sbps.size())
    {
        if (this->master.size())
            this->master.pop();
        if (this->slave.size())
            this->slave.pop();
        if (this->mbps.size())
            this->mbps.pop();
        if (this->sbps.size())
            this->sbps.pop();
    }
}

void *CallStack::operator new(size_t size)
{
    return cs_poll.malloc();
}

void CallStack::operator delete(void *p)
{
    cs_poll.free(p);
}

void CallStack::push(void *data)
{
    this->master.push(data);
}

void CallStack::pop()
{
    this->master.pop();
}

int CallStack::size() const
{
    return this->master.size();
}

void CallStack::save()
{
    this->mbps.push(this->master.size());
}

bool CallStack::roll()
{
    if (!mbps.size() || !master.size())
        return false;
    int mbp = this->mbps.top();
    int top = this->master.size();
    this->mbps.pop();
    if (mbp < top)
        this->sbps.push(this->slave.size());
    for (; mbp < top; top--)
    {
        void *e = this->master.top();
        this->master.pop();
        this->slave.push(e);
    }
    return true;
}

bool CallStack::pour()
{
    if (!sbps.size() || !slave.size())
        return false;
    int sbp = this->sbps.top();
    int top = this->slave.size();
    this->sbps.pop();
    for (; sbp < top; top--)
    {
        void *e = this->slave.top();
        this->slave.pop();
        this->master.push(e);
    }
    return true;
}