#ifndef __REMMEL_FFI_ENGINE__
#define __REMMEL_FFI_ENGINE__

#include "combustor.hpp"
#include "../../lib/safe_queue.hpp"
#include "../../lib/debug.hpp"

namespace remmel
{
#define GetLuaEngine LuaEngine::get_engine()

    class LuaEngine
    {
    private:
        static LuaEngine *instance;
        Mutex mut;
        Map<FStr, Pair<bool, uint32_t>> ns; // namespace
        Vec<lobject *> objects;

    public:
        LuaEngine();
        ~LuaEngine();
        static LuaEngine *get_engine();
        bool release(FStr, uint32_t);
        Pair<bool, uint32_t> trylock(FStr);
        Pair<lobject *, uint32_t> get(FStr);
        Pair<bool, FStr> eval(FStr, CStr);
        void alloc(FStr);
        void free(FStr);
    };

    LuaEngine *LuaEngine::instance = nullptr;
}

#endif