#ifndef __REMMEL_IO__
#define __REMMEL_IO__

#include "constant.hpp"

namespace remmel
{
    Str Strip(Str);

    enum class REM_FILE_STATUS
    {
        BINARY,
        STRING,
        // read mode
        LINE,
        STREAM,
    };

    class FileEngine
    {
    private:
        Str buf;

    public:
        FileEngine();
        FileEngine(const char *);
        ~FileEngine();
        Str Buf();
    };
}

#endif