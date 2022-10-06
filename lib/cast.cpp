#include "../include/lib/cast.hpp"

using namespace remmel;

REM_INT _int2bit_(int val)
{
    REM_INT temp;
    temp.val = val;
    return temp;
};

int bit2int(bitstream bits)
{
    REM_INT temp;
    for (int i = 0; i < INT_LEN; i++)
        temp.buf[i] = bits[i];
    return temp.val;
}

REM_LONG _long2bit_(long val)
{
    REM_LONG temp;
    temp.val = val;
    return temp;
};

long bit2long(bitstream bits)
{
    REM_LONG temp;
    for (int i = 0; i < LONG_LEN; i++)
        temp.buf[i] = bits[i];
    return temp.val;
}

REM_FLOAT _float2bit_(float val)
{
    REM_FLOAT temp;
    temp.val = val;
    return temp;
}

float bit2float(bitstream bits)
{
    REM_FLOAT temp;
    for (int i = 0; i < FLOAT_LEN; i++)
        temp.buf[i] = bits[i];
    return temp.val;
}

REM_DOUBLE _double2bit_(double val)
{
    REM_DOUBLE temp;
    temp.val = val;
    return temp;
}

float bit2float(bitstream bits)
{
    REM_DOUBLE temp;
    for (int i = 0; i < DOUBLE_LEN; i++)
        temp.buf[i] = bits[i];
    return temp.val;
}

REM_CHAR _char2bit_(char ch)
{
    REM_CHAR temp;
    temp.val = ch;
    return temp;
}

char bit2char(bitstream bits)
{
    REM_CHAR temp;
    for (int i = 0; i < 4; i++)
        temp.buf[i] = bits[i];
    return temp.val;
}

REM_POINTER _ptr2bit_(void *ptr)
{
    REM_POINTER temp;
    temp.val = ptr;
    return temp;
}

void *bit2ptr(bitstream bits)
{
    REM_POINTER temp;
    for (int i = 0; i < PTR_LEN; i++)
        temp.buf[i] = bits[i];
    return temp.val;
}