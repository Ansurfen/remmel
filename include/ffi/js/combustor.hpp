// Refer to v8go.h and v8go.cc from https://github.com/rogchap/v8go
// Thank Roger Chapman and the v8go contributors
#ifndef __REMMEL_ENGINE_COMBUSTOR__
#define __REMMEL_ENGINE_COMBUSTOR__

#include "supply.hpp"
#include "glue.hpp"
#include "cooling.hpp"

RValue RunScript(ContextPtr ctx, CStr code);

#define REACT(cylinder, fuel) RunScript(cylinder, fuel)

#define INIT_V8_ENV(p)                      \
    V8::InitializeICU();                    \
    V8::InitializeICUDefaultLocation(".");  \
    V8::InitializeExternalStartupData("."); \
    p = platform::NewDefaultPlatform();     \
    V8::InitializePlatform(p.get());        \
    V8::Initialize();                       \
    platform::InProcessStackDumping ipsd = platform::InProcessStackDumping::kEnabled

#define FIRE(p) INIT_V8_ENV(p)

template <JS_TYPE type>
void SetValue(ContextPtr, CStr, CStr);
template <JS_TYPE type>
Enable_if_t<type == JS_TYPE::JS_NULL> SetValue_Helper(ContextPtr, CStr, CStr);
template <JS_TYPE type>
Enable_if_t<type == JS_TYPE::JS_UNDEFINED> SetValue_Helper(ContextPtr, CStr, CStr);
template <JS_TYPE type>
Enable_if_t<type == JS_TYPE::JS_INTEGER> SetValue_Helper(ContextPtr, CStr, CStr);
template <JS_TYPE type>
Enable_if_t<type == JS_TYPE::JS_NUMBER> SetValue_Helper(ContextPtr, CStr, CStr);
template <JS_TYPE type>
Enable_if_t<type == JS_TYPE::JS_STRING> SetValue_Helper(ContextPtr, CStr, CStr);
template <JS_TYPE type>
Enable_if_t<type == JS_TYPE::JS_BOOLEAN> SetValue_Helper(ContextPtr, CStr, CStr);
template <JS_TYPE type>
Enable_if_t<type == JS_TYPE::JS_BIGINT> SetValue_Helper(ContextPtr, CStr, CStr);

Pair<BitArray, REM_TYPE> get_what(ContextPtr, CStr, JS_TYPE);

#endif