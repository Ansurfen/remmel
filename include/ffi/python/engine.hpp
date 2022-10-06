#include "combustor.hpp"
#include "../../lib/constant.hpp"
#include "../../lib/mem.hpp"
#include "../../lib/debug.hpp"
#include "../../lib/safe_queue.hpp"

class PyEngine
{
private:
    Mutex mut;
    Cylinder _main_;
    Map<FStr, Pair<bool, uint32_t>> ns; // namespace
    Vec<Cylinder> clds;
    Map<CStr, pobject> objects;
    Map<uint32_t, bool> garbages;

public:
    PyEngine();
    ~PyEngine();
    bool release(CStr, uint32_t);
    Pair<bool, uint32_t> trylock(CStr);
    Pair<Cylinder, uint32_t> get(CStr);
    void eval(CStr, CStr);
    void alloc(CStr);
    void free(CStr);
};