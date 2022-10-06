#include "python3.10/Python.h"
#include "../../lib/constant.hpp"

namespace remmel
{
#define pobject PyObject *

#define p_new Py_Initialize
#define p_free Py_Finalize

#define p_loadlib PyImport_GetModule

#define p_getvar PyObject_GetAttrString
#define p_getlong PyLong_AsLong

#define p_execstring PyRun_SimpleString
#define p_execfile PyRun_AnyFile

#define Cylinder PyThreadState *

    enum class PY_TYPE
    {
        PY_INTEGER,
        PY_NUMBER,
    };

    template <PY_TYPE type>
    using AutoPyType = Cond_t<type == PY_TYPE::PY_INTEGER, long,
                              Cond_t<type == PY_TYPE::PY_NUMBER, double, void *>>;

    CStr Mask();
}
