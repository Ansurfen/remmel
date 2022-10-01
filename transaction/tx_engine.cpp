#include "../include/transaction/tx_engine.hpp"

using namespace remmel;

TxEngine::TxEngine()
{
    for (uint8_t i = 0; i < 3; i++)
        this->callstacks.emplace_back(new CallStack);
    this->locks = new TxLocks(this->callstacks.size());
}

TxEngine::~TxEngine()
{
    delete this->locks;
    for (CallStack *callstack : this->callstacks)
        delete callstack;
}

TxEngine *TxEngine::get_engine()
{
    if (instance == nullptr)
        instance = new TxEngine;
    return instance;
}

void TxEngine::save(uint32_t td)
{
    this->callstacks[td]->save();
}

uint32_t TxEngine::begin()
{
    return this->locks->get();
}

void TxEngine::end(uint32_t td)
{
    this->locks->release(td);
}

void TxEngine::push(uint32_t td, void *data)
{
    this->callstacks[td]->push(data);
}

void TxEngine::pop(uint32_t td)
{
    this->callstacks[td]->pop();
}

bool TxEngine::roll(uint32_t td)
{
    return this->callstacks[td]->roll();
}

bool TxEngine::pour(uint32_t td)
{
    return this->callstacks[td]->pour();
}

void TxEngine::alloc()
{
    this->callstacks.emplace_back(new CallStack);
    this->locks->add();
}

void TxEngine::free(uint32_t td)
{
    this->locks->del();
}