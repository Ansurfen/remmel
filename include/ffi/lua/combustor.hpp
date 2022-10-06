#ifndef __REMMEL_FFI_OBJECT__
#define __REMMEL_FFI_OBJECT__

#include "glue.hpp"
#include "../../lib/constant.hpp"
#include "../../lib/mem.hpp"
#include "../../lib/bitarray.hpp"

namespace remmel
{
    enum class LUA_TYPE
    {
        INT,
        NUM,
        STR,
        BOOL,
        TABEL,
        NIL,
        TYPE
    };

    class lobject
    {
    private:
        lstack l;
        template <LUA_TYPE type>
        AutoLuaType<type> get_what(CStr);

        template <LUA_TYPE type, class T = AutoLuaType<type>>
        Enable_if_t<type == LUA_TYPE::INT, T> get_what_helper();
        template <LUA_TYPE type, class T = AutoLuaType<type>>
        Enable_if_t<type == LUA_TYPE::NUM, T> get_what_helper();
        template <LUA_TYPE type, class T = AutoLuaType<type>>
        Enable_if_t<type == LUA_TYPE::STR, T> get_what_helper();
        template <LUA_TYPE type, class T = AutoLuaType<type>>
        Enable_if_t<type == LUA_TYPE::BOOL, T> get_what_helper();

    public:
        lobject();
        ~lobject();
        void *operator new(size_t);
        void operator delete(void *);
        Pair<bool, FStr> eval(CStr) noexcept;
        BitArray get_var(CStr, LUA_TYPE) noexcept;
        template <LUA_TYPE type>
        AutoLuaType<type> get_field(CStr) noexcept;
        template <LUA_TYPE type>
        AutoLuaType<type> get_index(long long) noexcept;
    };

    template <LUA_TYPE type>
    using AutoLuaType =
        Cond_t<type == LUA_TYPE::INT, long long,
               Cond_t<type == LUA_TYPE::NUM, double,
                      Cond_t<type == LUA_TYPE::STR, Str,
                             Cond_t<type == LUA_TYPE::BOOL, bool,
                                    Cond_t<type == LUA_TYPE::TABEL, lobject,
                                           Cond_t<type == LUA_TYPE::TYPE, LUA_TYPE, Runtime_error>>>>>>;

    MemPool<sizeof(lobject), 4> lo_poll;
}

#endif