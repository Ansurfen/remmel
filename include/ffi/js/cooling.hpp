// Refer to v8go.h and v8go.cc from https://github.com/rogchap/v8go
// Thank Roger Chapman and the v8go contributors
#ifndef __REMMEL_ENGINE_COOLING__
#define __REMMEL_ENGINE_COLLING__

#include "glue.hpp"

RError ExceptionError(TryCatch &, IsolatePtr, Local<Context>);
ValuePtr IsolateThrowException(IsolatePtr, ValuePtr);
void recycle(CStr);

#endif