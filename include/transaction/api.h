#ifndef __REMMEL_TX_API__
#define __REMMEL_TX_API__

#include "../lib/libc.h"

REM_API uint32_t begin();
REM_API void end(uint32_t);
REM_API RET get();
REM_API void save(uint32_t);
REM_API Boolean rollback(uint32_t);
REM_API void alloc();        // new a callstack
REM_API void free(uint32_t); // free callstack

#endif