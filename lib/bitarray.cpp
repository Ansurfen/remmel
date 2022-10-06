#include "../include/lib/bitarray.hpp"

using namespace remmel;

BitArray::BitArray()
{
    this->len = PTR_LEN;
    this->bits = new bits_t[PTR_LEN];
}

BitArray::BitArray(size_t size)
{
    this->len = size;
    this->bits = new bits_t[size];
}

BitArray::BitArray(char val)
{
    this->len = CHAR_LEN;
    this->bits = (bits_t *)val;
}

BitArray::BitArray(bool val)
{
    this->len = BOOL_LEN;
    this->bits = _bool2bit_(val).buf;
}

BitArray::BitArray(int val)
{
    this->len = INT_LEN;
    this->bits = _int2bit_(val).buf;
}

BitArray::BitArray(long val)
{
    this->len = LONG_LEN;
    this->bits = _long2bit_(val).buf;
}

BitArray::BitArray(long long val)
{
    this->len = LLONG_LEN;
    this->bits = _llong2bit_(val).buf;
}

BitArray::BitArray(float val)
{
    this->len = FLOAT_LEN;
    this->bits = _float2bit_(val).buf;
}

BitArray::BitArray(double val)
{
    this->len = DOUBLE_LEN;
    this->bits = _double2bit_(val).buf;
}

BitArray::~BitArray()
{
    delete this->bits;
}

BitArray::operator char() const
{
    return this->bits[0];
}

BitArray::operator bool() const
{
    return bit2bool(this->bits);
}

BitArray::operator int() const
{
    return bit2int(this->bits);
}

BitArray::operator long() const
{
    return bit2long(this->bits);
}

BitArray::operator long long() const
{
    return bit2llong(this->bits);
}

BitArray::operator float() const
{
    return bit2float(this->bits);
}

BitArray::operator double() const
{
    return bit2double(this->bits);
}

BitArray::operator char *()
{
    return (char *)this->bits;
}

BitArray::operator const char *() const
{
    return reinterpret_cast<const char *>(this->bits);
}

BitArray::operator Str() const
{
    return Str(reinterpret_cast<char *>(this->bits), this->len);
}

BitArray::operator FStr() const
{
    return FStr(reinterpret_cast<char *>(this->bits), this->len);
}

void BitArray::operator=(char val)
{
    if (this->len <= CHAR_LEN)
        this->bits = (bits_t *)val;
}

void BitArray::operator=(bool val)
{
    if (this->len <= BOOL_LEN)
        this->bits = _bool2bit_(val).buf;
}

void BitArray::operator=(int val)
{
    if (this->len <= INT_LEN)
        this->bits = _int2bit_(val).buf;
}

void BitArray::operator=(long val)
{
    if (this->len <= LONG_LEN)
        this->bits = _long2bit_(val).buf;
}

void BitArray::operator=(long long val)
{
    if (this->len <= LLONG_LEN)
        this->bits = _llong2bit_(val).buf;
}

void BitArray::operator=(float val)
{
    if (this->len <= FLOAT_LEN)
        this->bits = _float2bit_(val).buf;
}

void BitArray::operator=(double val)
{
    if (this->len <= DOUBLE_LEN)
        this->bits = _double2bit_(val).buf;
}

void BitArray::operator=(const char *val)
{
    if (this->len <= CHAR_LEN) // this is error
        this->bits = (bits_t *)val;
}

void BitArray::operator=(const Str &val)
{
    if (this->len <= val.length())
        this->bits = (bits_t *)val.data();
}

void BitArray::operator=(const FStr &val)
{
    if (this->len <= val.length())
        this->bits = (bits_t *)val.data();
}

uint32_t BitArray::Size() const
{
    return this->len;
}

void BitArray::Set(uint32_t index, bits_t val)
{
    if (index >= this->len)
        return;
    this->bits[index] = val;
}

void BitArray::SetAll(bits_t val)
{
    for (uint32_t i = 0; i < this->len; i++)
        this->bits[i] = val;
}

bool BitArray::Get(uint32_t index)
{
    if (index >= this->len)
        return false;
    return this->bits[index];
}

bool BitArray::operator[](uint32_t index)
{
    if (index >= this->len)
        return false;
    return this->bits[index];
}