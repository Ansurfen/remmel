#include "../include/transaction/api.h"
#include "../include/transaction/tx_engine.hpp"

using namespace remmel;

REM_API uint32_t begin()
{
    return GetTxEngine->begin();
}

REM_API void end(uint32_t td)
{
    GetTxEngine->end(td);
}

REM_API void save(uint32_t td)
{
    GetTxEngine->save(td);
}

REM_API Boolean rollback(uint32_t td)
{
    return GetTxEngine->roll(td) ? B_TRUE : B_FALSE;
}

REM_API void alloc()
{
    GetTxEngine->alloc();
}

REM_API void free(uint32_t td)
{
    GetTxEngine->free(td);
}