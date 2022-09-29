#ifndef __REMMEL_CAST__
#define __REMMEL_CAST__

#include "constant.hpp"

namespace remmel
{
    union REM_INT
    {
        int val;
        bits_t buf[INT_LEN];
    };

    union REM_FLOAT
    {
        float val;
        bits_t buf[FLOAT_LEN];
    };

    union REM_LONG
    {
        long val;
        bits_t buf[LONG_LEN];
    };

    union REM_LLONG
    {
        long long val;
        bits_t buf[LLONG_LEN];
    };

    union REM_CHAR
    {
        char val;
        bits_t buf[4];
    };

    union REM_DOUBLE
    {
        double val;
        bits_t buf[DOUBLE_LEN];
    };

    union REM_POINTER
    {
        void *val;
        bits_t buf[PTR_LEN];
    };

    REM_INT _int2bit_(int);
    int bit2int(bitstream);
    REM_LONG _long2bit_(long);
    long bit2long(bitstream);
    REM_LLONG _llong2bit_(long long);
    long long bit2llong(bitstream);
    REM_FLOAT _float2bit_(float);
    float bit2float(bitstream);
    REM_CHAR _char2bit_(char);
    char bit2char(bitstream);
    REM_POINTER _ptr2bit_(void *);
    void *bit2ptr(bitstream);

#define str2bit(str) (bitstream) str
#define ptr2bit(val) reinterpret_cast<bitstream>(_ptr2bit_(val).buf)
#define int2bit(val) reinterpret_cast<bitstream>(_int2bit_(val).buf)
#define long2bit(val) reinterpret_cast<bitstream>(_long2bit_(val).buf)
#define float2bit(val) reinterpret_cast<bitstream>(_float2bit_(val).buf)
#define char2bit(val) reinterpret_cast<bitstream>(_char2bit_(val).buf)
}

#endif