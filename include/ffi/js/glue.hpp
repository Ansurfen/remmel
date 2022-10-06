// Refer to v8go.h and v8go.cc from https://github.com/rogchap/v8go
// Thank Roger Chapman and the v8go contributors
#ifndef __REMMEL_ENGINE_GLUE__
#define __REMMEL_ENGINE_GLUE__

#include "v8/include/v8.h"
#include "v8/include/libplatform/libplatform.h"
#include "../../lib/bitarray.hpp"

using namespace v8;
using namespace remmel;

typedef Isolate *IsolatePtr;

typedef struct
{
    CStr msg;
    CStr location;
    CStr stack;
} RError;

typedef struct
{
    IsolatePtr iso;
    Persistent<Context> instance;
} * ContextPtr;

typedef struct
{
    IsolatePtr iso;
    ContextPtr ctx;
    Persistent<Value, CopyablePersistentTraits<Value>> instance;
} * ValuePtr;

typedef struct
{
    bool ok;
    ValuePtr value;
    RError error;
} RValue;

typedef struct
{
    IsolatePtr iso;
    Persistent<Template> instance;
} * TemplatePtr;

typedef struct
{
    CStr data;
    int length;
    RError error;
} RtnString;

typedef struct
{
    const uint64_t *word_array;
    int word_count;
    int sign_bit;
} ValueBigInt;

enum class JS_TYPE
{
    JS_NULL,
    JS_UNDEFINED,
    JS_INTEGER,
    JS_STRING,
    JS_BOOLEAN,
    JS_NUMBER,
    JS_BIGINT
};

template <JS_TYPE type> /* void* -> nullptr */
using AutoJSType = Cond_t<type == JS_TYPE::JS_NULL, void *,
                          Cond_t<type == JS_TYPE::JS_UNDEFINED, void *,
                                 Cond_t<type == JS_TYPE::JS_INTEGER, int,
                                        Cond_t<type == JS_TYPE::JS_STRING, Str,
                                               Cond_t<type == JS_TYPE::JS_BOOLEAN, bool,
                                                      Cond_t<type == JS_TYPE::JS_NUMBER, double,
                                                             Cond_t<type == JS_TYPE::JS_BIGINT, ValueBigInt, void *>>>>>>>;

#define DECLARE_ISOLATE_SCOPE(iso)     \
    Locker locker(iso);                \
    Isolate::Scope isolate_scope(iso); \
    HandleScope handle_scope(iso)

#define DECLARE_ISOLATE_SCOPE_FROM_CTX(ctx) \
    IsolatePtr iso = ctx;                   \
    DECLARE_ISOLATE_SCOPE(iso);             \
    TryCatch try_catch(iso)

#define DECLARE_ISOLATE_SCOPE_FROM_VALUE DECLARE_ISOLATE_SCOPE_FROM_CTX

#define DECLARE_LOCAL_CONTEXT(ctx)                     \
    DECLARE_ISOLATE_SCOPE_FROM_CTX(ctx->iso);          \
    Local<Context> local_ctx = ctx->instance.Get(iso); \
    Context::Scope context_scope(local_ctx)

#define DECLARE_LOCAL_VALUE(val)                       \
    DECLARE_ISOLATE_SCOPE_FROM_VALUE(val->iso);        \
    ContextPtr ctx = val->ctx;                         \
    Local<Context> local_ctx = ctx->instance.Get(iso); \
    Context::Scope context_scope(local_ctx);           \
    Local<Value> value = val->instance.Get(iso)

#define DECLARE_LOCAL_TEMPLATE(tmpl_ptr) \
    Isolate *iso = tmpl_ptr->iso;        \
    DECLARE_ISOLATE_SCOPE(iso);          \
    Local<Template> tmpl = tmpl_ptr->instance.Get(iso);

IsolatePtr NewIsolate();
ContextPtr NewContext(IsolatePtr);
void IsolateFree(IsolatePtr);
void ContextFree(ContextPtr);

ValuePtr NewValueInteger(ContextPtr, int32_t);
ValuePtr NewValueIntegerFromUnsigned(ContextPtr, uint32_t);
RValue NewValueString(ContextPtr, CStr, int);
ValuePtr NewValueNull(ContextPtr);

int Value2Boolean(ValuePtr);
int32_t Value2Int32(ValuePtr);
int64_t Value2Integer(ValuePtr);
double Value2Number(ValuePtr);
RtnString Value2DetailString(ValuePtr);
FStr Value2String(ValuePtr);
uint32_t Value2Uint32(ValuePtr);
ValueBigInt Value2BigInt(ValuePtr);
RValue Value2Object(ValuePtr);
int ValueSameValue(ValuePtr, ValuePtr);

CStr LangVersion();
CStr Mask();

#define ByProduct RValue
#define Cylinder ContextPtr

#endif