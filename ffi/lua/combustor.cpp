#include "../../include/ffi/lua/combustor.hpp"

using namespace remmel;

lobject::lobject()
{
    this->l = new_default_lstack();
    if (!l)
        throw Runtime_error{"fail to init lstack"};
}

lobject::~lobject()
{
    delete this->l;
}

void *lobject::operator new(size_t size)
{
    return lo_poll.malloc();
}

void lobject::operator delete(void *p)
{
    lo_poll.free(p);
}

Pair<bool, FStr> lobject::eval(CStr code) noexcept
{
    error err = l_execstring(this->l, code);
    if (err)
    {
        FStr msg = l_getstring(this->l, l_top);
        l_pop(this->l, 1);
        return {false, msg};
    }
    return {true, {}};
}

BitArray lobject::get_var(CStr name, LUA_TYPE type)
{
    BitArray bits;
    switch (type)
    {
    case LUA_TYPE::INT:
        bits = this->get_what<LUA_TYPE::INT>(name);
        break;
    case LUA_TYPE::NUM:
        bits = this->get_what<LUA_TYPE::NUM>(name);
        break;
    case LUA_TYPE::STR:
        bits = this->get_what<LUA_TYPE::STR>(name);
        break;
    case LUA_TYPE::BOOL:
        bits = this->get_what<LUA_TYPE::BOOL>(name);
        break;
    case LUA_TYPE::TABEL:
        break;
    case LUA_TYPE::NIL:
        break;
    case LUA_TYPE::TYPE:
        break;
    default:
        break;
    }
}

template <LUA_TYPE type>
AutoLuaType<type> lobject::get_what(CStr name)
{
    l_getvar(this->l, name);
    return this->get_what_helper<LUA_TYPE::INT>();
}

template <LUA_TYPE type, class T>
Enable_if_t<type == LUA_TYPE::INT, T> lobject::get_what_helper()
{
    return l_getint(this->l, l_top);
}

template <LUA_TYPE type, class T>
Enable_if_t<type == LUA_TYPE::NUM, T> lobject::get_what_helper()
{
    return l_getnumber(this->l, l_top);
}

template <LUA_TYPE type, class T>
Enable_if_t<type == LUA_TYPE::STR, T> lobject::get_what_helper()
{
    return l_getstring(this->l, l_top);
}

template <LUA_TYPE type, class T>
Enable_if_t<type == LUA_TYPE::BOOL, T> lobject::get_what_helper()
{
    return l_getbool(this->l, l_top);
}