#ifndef __REMMEL_IR__
#define __REMMEL_IR__

#include "../lib/libc.h"

#define IR_NODE void *
#define Instructions void *
#define STR_SET void *

REM_API IR_NODE parse(STR_SET);
REM_API Instructions eval(IR_NODE);

#endif