#include "../include/ffi/api.h"
#include "../include/ffi/lua/engine.hpp"

using namespace remmel;

REM_API RET eval(CStr ns, CStr data)
{
    RET ret;
#ifdef __REMMEL_LUA__
    Pair<bool, FStr> res = GetLuaEngine->eval(ns, data);
    ret.ok = res.first;
    ret.msg = res.second.data();
#elif __REMMEL_PY__
#elif __REMMEL_JS__
#endif
    return ret;
}

REM_API RET del(CStr ns, CStr ident)
{
}