#include "../../lib/constant.hpp"
#include "combustor.hpp"
#include "../../lib/debug.hpp"

class JSEngine
{
private:
    UniPtr<Platform> p;
    Vec<IsolatePtr> processors;
    IsolatePtr late;
    Vec<Cylinder> clds;
    Map<CStr, Pair<bool, uint32_t>> ns; // namespace
    Map<uint32_t, bool> garbages;
    Mutex mut;
    uint32_t cnt;

public:
    JSEngine(CStr);
    ~JSEngine();
    Pair<bool, uint32_t> trylock(CStr);
    bool release(CStr, uint32_t);
    Pair<Cylinder, uint32_t> get(CStr);
    void eval(CStr, CStr);
    void set_val(CStr, CStr, CStr);
    void get_val(CStr, CStr, JS_TYPE);
    void dec_func(CStr, CStr);
    void alloc(CStr);
    void free(CStr);
};