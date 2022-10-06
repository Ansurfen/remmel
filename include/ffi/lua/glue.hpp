#ifndef __REMMEL_FFI_MACRO__
#define __REMMEL_FFI_MACRO__
#define __REMMEL_LUA__

#include "lua/lua.hpp"
#include "../../lib/constant.hpp"

namespace remmel
{
#define lstack lua_State *

#define l_new() luaL_newstate()
#define l_free(l) lua_close(l)

#define l_getstring lua_tostring
#define l_getnumber lua_tonumber
#define l_getbool lua_toboolean
#define l_getint lua_tointeger
#define l_gettable lua_gettable

#define l_loadfile(l, fn) luaL_loadfile(l, fn)
#define l_execfile(l, fn) luaL_dofile(l, fn)
#define l_execstring(l, s) luaL_dostring(l, s)

#define l_geti(l, i, n) lua_geti(l, i, n);
#define l_getfiled(l, n, name) lua_getfield(l, n, name)
#define l_getvar(l, name) lua_getglobal(l, name)
#define l_setvar(l, name) lua_setglobal(l, name)

#define l_pop(l, n) lua_pop(l, n)
#define l_loadlibs(l) luaL_openlibs(l)

#define l_top -1
#define l_top_offset -1
#define l_bottom 1
#define l_bootom_offset 1

#define l_gettop lua_gettop
#define l_syscall(l, n, r, f) lua_pcall(l, n, r, f)

#define l_putstring(l, s) lua_pushstring(l, s)
#define l_putnumber(l, n) lua_pushnumber(l, n)
#define l_putnil(l) lua_pushnil(l)
#define l_putbool(l, b) lua_pushboolean(l, b)

#define l_type(l, i) lua_type(l, i)
#define l_typeis(l, t) (l_type(l, l_gettop(l)) == t)

#define l_delete(l, name)  \
    do                     \
    {                      \
        l_getvar(l, name); \
        l_pop(l, 1);       \
        l_putnil(l);       \
        l_setvar(l, name); \
    } while (0)

#define l_checkoverflow(l, idx)    \
    do                             \
    {                              \
        if (!(l_gettop(l) >= idx)) \
            throw;                 \
    } while (0)

    lstack new_lstack();
    lstack new_default_lstack();

    void DumpLStack(lstack);

#define error int

    CStr Mask();
}

#endif