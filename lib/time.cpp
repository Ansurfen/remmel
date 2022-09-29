#include "../include/lib/time.hpp"

using namespace remmel;

Str CurTime()
{
    struct tm t;
    time_t now;
    time(&now);
    localtime_s(&t, &now);
    char ret[20] = "\0";
    sprintf_s(ret, 20, "%.4d-%.2d-%.2d %.2d:%.2d:%.2d", t.tm_year + 1900, t.tm_mon + 1, t.tm_mday, t.tm_hour, t.tm_min, t.tm_sec);
    return ret;
}