#ifndef __REMMEL_ENGINE_COMBUSTOR__
#define __REMMEL_ENGINE_COMBUSTOR__

#include "glue.hpp"
#include "../../lib/bitarray.hpp"

namespace remmel
{
    void RunScript(PyInterpreterState *, CStr);

    Pair<pobject, pobject> get_what(PyInterpreterState *, pobject, CStr);
    Pair<BitArray, pobject> get(PyInterpreterState *, pobject, CStr);
}

#endif