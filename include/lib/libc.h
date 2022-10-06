#ifndef __REMMEL_LIBC__
#define __REMMEL_LIBC__

#define REM_API extern "C" _declspec(dllexport)

#include <stdint.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stddef.h>

#define CStr const char *

enum Boolean
{
    B_TRUE,
    B_FALSE,
};

struct RET
{
    uint8_t ok;
    CStr msg;
};

#endif