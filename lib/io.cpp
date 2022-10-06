#include "../include/lib/io.hpp"

using namespace remmel;

Str Strip(Str s)
{
    if (s.empty())
        return s;
    s.erase(0, s.find_first_not_of(" \r\n"));
    s.erase(s.find_last_not_of(" \r\n") + 1);
    return s;
}

FStr ReadFile(Str name)
{
    std::ifstream fp;
    fp.open(name, std::ios::in);
    if (!fp.is_open())
    {
        WARN("fail to open the file");
        return "";
    }
    char ch;
    Str ret;
    while ((ch = fp.get()) != EOF)
        ret += ch;
    fp.close();
    return ret;
}