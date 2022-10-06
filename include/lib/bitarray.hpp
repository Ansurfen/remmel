#ifndef __REMMEL_BIT_ARRAY__
#define __REMMEL_BIT_ARRAY__

#include "constant.hpp"
#include "cast.hpp"

namespace remmel
{
    class BitArray
    {
    private:
        uint32_t len;
        bitstream bits;

    public:
        BitArray();
        BitArray(size_t);
        BitArray(char);
        BitArray(bool);
        BitArray(int);
        BitArray(long);
        BitArray(long long);
        BitArray(float);
        BitArray(double);
        BitArray(const char *);
        BitArray(const Str &);
        BitArray(const FStr &);
        ~BitArray();

        void operator=(char);
        void operator=(bool);
        void operator=(int);
        void operator=(long);
        void operator=(long long);
        void operator=(float);
        void operator=(double);
        void operator=(const char *);
        void operator=(const Str &);
        void operator=(const FStr &);

        operator char() const;
        operator bool() const;
        operator int() const;
        operator long() const;
        operator long long() const;
        operator float() const;
        operator double() const;
        operator char *();
        operator const char *() const;
        operator Str() const;
        operator FStr() const;

        uint32_t Size() const;
        void Set(uint32_t, bits_t);
        void SetAll(bits_t);
        bool Get(uint32_t);
        bool operator[](uint32_t);
    };
}

#endif