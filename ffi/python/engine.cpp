#include "../../include/ffi/python/engine.hpp"

using namespace remmel;

PyEngine::PyEngine()
{
    p_new();
    if (!Py_IsInitialized())
        FATAL("fail to init python engine");
    this->_main_ = PyThreadState_GET();
}

PyEngine::~PyEngine()
{
    PyThreadState_Swap(this->_main_);
    p_free();
}

bool PyEngine::release(CStr name, uint32_t lock)
{
    if (this->ns[name].second != lock)
    {
        WARN("invalid lock at namespace");
        return false;
    }
    if (this->garbages[lock])
    {
        UniLock<Mutex> lck(this->mut);
        if (this->garbages.find(lock) != this->garbages.end() && this->garbages[lock]) // Concurrency security
        {
            this->garbages.erase(lock);
            Pair<bool, uint32_t> res = this->ns[name];
            this->ns.erase(name);
            this->clds.erase(this->clds.begin() + res.second);
            return true;
        }
    }
    this->ns[name].first = ns_unlock;
    return true;
}

Pair<bool, uint32_t> PyEngine::trylock(CStr name)
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

Pair<Cylinder, uint32_t> PyEngine::get(CStr name)
{
    Pair<bool, uint32_t> res = this->trylock(name);
    if (!res.first)
        return {nullptr, -1};
    return {this->clds[res.second], res.first};
}

void PyEngine::eval(CStr name, CStr code)
{
    Pair<Cylinder, uint32_t> res = this->get(name);
    if (res.second == -1)
    {
        WARN("fail to get pythreadstate");
        return;
    }
    UniLock<Mutex> lock(this->mut);
    this->_main_ = PyEval_SaveThread();
    RunScript(res.first->interp, code);
    PyEval_RestoreThread(this->_main_);
    if (!this->release(name, res.second))
        WARN("fail to release lock");
}

void PyEngine::alloc(CStr name)
{
    if (this->ns.find(name) != this->ns.end())
        WARN("interpreter has been created");
    UniLock<Mutex> lock(this->mut);
    this->clds.emplace_back(Py_NewInterpreter());
    this->ns[name] = {ns_unlock, this->clds.size() - 1};
}

void PyEngine::free(CStr name)
{
    if (this->ns.find(name) != this->ns.end())
        WARN("fail to seach interpreter");
    UniLock<Mutex> lock(this->mut);
    Pair<bool, uint32_t> res = this->ns[name];
    if (res.first == ns_lock)
    {
        this->garbages[res.second] = true;
        return;
    }
    this->ns.erase(name);
    this->clds.erase(this->clds.begin() + res.second);
}
