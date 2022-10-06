#include "../include/store/store.hpp"

using namespace remmel;

void Store::init(uint8_t count, ...)
{
    if (count <= 0)
        return;
    va_list arg_ptr;
    va_start(arg_ptr, count);
    for (uint8_t i = 0; i < count; i++)
    {
        IndexMeta im = va_arg(arg_ptr, IndexMeta);
        this->open(im.mask, im.path);
    }
    va_end(arg_ptr);
}

void Store::open(FStr mask, FStr path)
{
    uint8_t len = mask.length();
    if (len >= 12)
    {
        WARN("");
        return;
    }
    Str name = mask.data();
    name += MD5(path.data()).substr(0, 12 - len);
    // to open file, save every fp
    // 
}