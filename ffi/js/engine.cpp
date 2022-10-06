#include "../../include/ffi/js/engine.hpp"

using namespace remmel;

JSEngine::JSEngine(CStr argv)
{
    FIRE(this->p);
    this->cnt = 0;
}

JSEngine::~JSEngine()
{
    V8::Dispose();
    V8::ShutdownPlatform();
    this->p.reset();
}

bool JSEngine::release(CStr name, uint32_t lock)
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

Pair<bool, uint32_t> JSEngine::trylock(CStr name)
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

void JSEngine::alloc(CStr name)
{
    if (this->ns.find(name) != this->ns.end())
        WARN("Cylinder has been created");
    UniLock<Mutex> lock(this->mut);
    if (this->cnt % 3 == 0) // alloc new processor(isolate)
    {
        this->late = NewIsolate();
        this->processors.emplace_back(this->late);
        this->cnt = 0;
    }
    else // get old processor
        this->cnt++;
    this->clds.emplace_back(NewContext(this->late));
    this->ns[name] = {ns_unlock, this->clds.size() - 1};
}

void JSEngine::free(CStr name)
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
    ContextFree(this->clds[res.second]);
    this->ns.erase(name);
    this->clds.erase(this->clds.begin() + res.second);
    // delete isolateptr
}

void JSEngine::eval(CStr name, CStr code)
{
    Pair<Cylinder, uint32_t> res = this->get(name);
    if (res.second == -1)
    {
        WARN("fail to get context ptr");
        return;
    }
    UniLock<Mutex> lock(this->mut);
    ByProduct by_product = REACT(res.first, code);
    if (!by_product.ok)
        WARN("fail to get value, err: %s", by_product.error.msg);
    if (!this->release(name, res.second))
        WARN("fail to release lock");
}

void JSEngine::get_val(CStr name, CStr ident, JS_TYPE type)
{
    Pair<Cylinder, uint32_t> res = this->get(name);
    if (res.second == -1)
    {
        WARN("fail to get Cylinder");
        return;
    }
    UniLock<Mutex> lock(this->mut);
    get_what(res.first, ident, type);
}

Pair<Cylinder, uint32_t> JSEngine::get(CStr name)
{
    Pair<bool, uint32_t> res = this->trylock(name);
    if (!res.first)
        return {nullptr, -1};
    return {this->clds[res.second], res.first};
}

void test()
{
    JSEngine *je = new JSEngine("");
    je->alloc("ctx1");
    je->eval("ctx1", "fib(10)");
    delete je;
}