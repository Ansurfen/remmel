#ifndef __REMMEL_FFI_API__
#define __REMMEL_FFI_API__

#include "../lib/libc.h"

REM_API RET init(CStr);
REM_API RET info(); // get mask
REM_API RET check(CStr);
REM_API RET eval(CStr, CStr);
REM_API RET get(CStr, CStr);
REM_API RET get_bits(CStr, CStr, CStr);
REM_API void free(CStr);
REM_API RET del(CStr, CStr);
REM_API RET mount_func(CStr, CStr);
REM_API RET unmount_func(CStr, CStr);

#endif