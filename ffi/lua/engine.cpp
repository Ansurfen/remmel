#include "../../include/ffi/lua/engine.hpp"

using namespace remmel;

LuaEngine::LuaEngine() {}

LuaEngine::~LuaEngine()
{
    for (lobject *object : this->objects)
        delete object;
}

LuaEngine *LuaEngine::get_engine()
{
    if (instance == nullptr)
        instance = new LuaEngine;
    return instance;
}

Pair<bool, uint32_t> LuaEngine::trylock(FStr name)
{
    if (this->ns.find(name) == this->ns.end())
        return {false, -1};
    UniLock<Mutex> lock(this->mut);
    Pair<bool, uint32_t> res = this->ns[name];
    if (res.first == ns_unlock)
    {
        res.first = true;
        this->ns[name].first = ns_lock;
    }
    else
    {
        res.first = false;
        res.second = -1;
    }
    return res;
}

bool LuaEngine::release(FStr name, uint32_t lock)
{
    if (this->ns[name].second != lock)
    {
        WARN("invalid lock at namespace");
        return false;
    }
    this->ns[name].first = ns_unlock;
    return true;
}

Pair<lobject *, uint32_t> LuaEngine::get(FStr name)
{
    Pair<bool, uint32_t> res = this->trylock(name);
    if (!res.first)
        return {nullptr, -1};
    return {this->objects[res.second], res.first};
}

Pair<bool, FStr> LuaEngine::eval(FStr name, CStr code)
{
    Pair<lobject *, uint32_t> res = this->get(name);
    if (res.second == -1)
        return {false, "fail to get lua object"};
    UniLock<Mutex> lck(this->mut);
    Pair<bool, FStr> ret = this->objects[res.second]->eval(code);
    if (!this->release(name, res.second))
        WARN("fail to release lock");
    return ret;
}