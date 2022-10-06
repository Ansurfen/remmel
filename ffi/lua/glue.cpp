#include "../../include/ffi/lua/glue.hpp"

using namespace remmel;

lstack new_lstack()
{
    return l_new();
}

lstack new_default_lstack()
{
    lstack l = l_new();
    l_loadlibs(l);
    return l;
}

void DumpLStack(lstack l)
{
    int i = l_gettop(l);
    printf("----- Stack Dump -----\n");
    while (i)
    {
        switch (l_type(l, i))
        {
        case LUA_TTABLE:
            printf("[%d]\ttable\n", i);
            break;
        case LUA_TNIL:
            printf("[%d]\tnull\n", i);
            break;
        case LUA_TSTRING:
            printf("[%d]\tstring(%s)", i, l_getstring(l, i));
            break;
        case LUA_TNUMBER:
            printf("[%d]\tnumber(%d)", i, l_getnumber(l, i));
            break;
        default:
            break;
        }
        i--;
    }
    printf("----- Stack End -----\n");
}

CStr Mask()
{
    return "REMLUA";
}