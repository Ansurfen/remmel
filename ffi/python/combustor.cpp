#include "../../include/ffi/python/combustor.hpp"

using namespace remmel;

void RunScript(PyInterpreterState *interp, CStr code)
{
    // create a new thread state for the the sub interpreter interp
    PyThreadState *temp = PyThreadState_New(interp);
    // make it the current thread state and acquire the GIL
    PyEval_RestoreThread(temp);
    // at this point:
    // 1. You have the GIL
    // 2. You have the right thread state - a new thread state (this thread was not created by python) in the context of interp
    PyRun_SimpleString(code);
    // clear ts
    PyThreadState_Clear(temp);
    // delete the current thread state and release the GIL
    PyThreadState_DeleteCurrent();
}

Pair<pobject, pobject> remmel::get_what(PyInterpreterState *interp, pobject p, CStr name)
{
    PyThreadState *temp = PyThreadState_New(interp);
    PyEval_RestoreThread(temp);
    if (p == nullptr)
        p = p_loadlib(PyUnicode_FromString("__main__"));
    pobject var = p_getvar(p, name);
    PyThreadState_Clear(temp);
    PyThreadState_DeleteCurrent();
    return {var, p};
}

Pair<BitArray, pobject> get(PyInterpreterState *interp, pobject p, CStr name, PY_TYPE t)
{
    Pair<pobject, pobject> res = get_what(interp, p, name);
    BitArray bits;
    REM_TYPE type = REM_TYPE::EOT;
    switch (t)
    {
    case PY_TYPE::PY_INTEGER:
        bits = BitArray(long(PyLong_AsLong(res.first)));
        break;
    case PY_TYPE::PY_NUMBER:
        bits = BitArray(double(PyFloat_AsDouble(res.first)));
        break;
    default:
        break;
    }
    return {bits, p};
}