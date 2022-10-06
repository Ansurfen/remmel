#include "../../include/ffi/js/glue.hpp"
#include "../../include/ffi/js/cooling.hpp"
#include "../../include/ffi/js/combustor.hpp"

IsolatePtr NewIsolate()
{
    Isolate::CreateParams create_params;
    create_params.array_buffer_allocator = ArrayBuffer::Allocator::NewDefaultAllocator();
    return Isolate::New(create_params);
}

ContextPtr NewContext(IsolatePtr iso)
{
    DECLARE_ISOLATE_SCOPE(iso);
    Local<ObjectTemplate> g_tmpl = ObjectTemplate::New(iso);
    Local<Context> local_ctx = Context::New(iso, nullptr, g_tmpl);
    ContextPtr ctx;
    ctx->instance.Reset(iso, local_ctx);
    ctx->iso = iso;
    return ctx;
}

void IsolateFree(IsolatePtr iso)
{
    if (!iso)
        return;
    iso->Dispose();
}

void ContextFree(ContextPtr ctx)
{
    if (!ctx)
        return;
    ctx->instance.Reset();
    delete ctx;
}

ValuePtr NewValueInteger(ContextPtr ctx, int32_t v)
{
    DECLARE_ISOLATE_SCOPE_FROM_CTX(ctx->iso);
    ValuePtr val;
    val->iso = iso;
    val->ctx = ctx;
    val->instance = Persistent<Value, CopyablePersistentTraits<Value>>(iso, Integer::New(iso, v));
    return val;
}

int Value2Boolean(ValuePtr ptr)
{
    DECLARE_LOCAL_VALUE(ptr);
    return value->BooleanValue(iso);
}

int32_t Value2Int32(ValuePtr ptr)
{
    DECLARE_LOCAL_VALUE(ptr);
    return value->Int32Value(local_ctx).ToChecked();
}

int64_t Value2Integer(ValuePtr ptr)
{
    DECLARE_LOCAL_VALUE(ptr);
    return value->IntegerValue(local_ctx).ToChecked();
}

double Value2Number(ValuePtr ptr)
{
    DECLARE_LOCAL_VALUE(ptr);
    return value->NumberValue(local_ctx).ToChecked();
}

RtnString Value2DetailString(ValuePtr ptr)
{
    DECLARE_LOCAL_VALUE(ptr);
    RtnString rtn = {0};
    Local<String> str;
    if (!value->ToDetailString(local_ctx).ToLocal(&str))
    {
        rtn.error = ExceptionError(try_catch, iso, local_ctx);
        return rtn;
    }
    String::Utf8Value ds(iso, str);
    rtn.data = FStr(*ds).data();
    rtn.length = ds.length();
    return rtn;
}

FStr Value2String(ValuePtr ptr)
{
    DECLARE_LOCAL_VALUE(ptr);
    String::Utf8Value src(iso, value);
    return FStr(*src, src.length());
}

uint32_t Value2Uint32(ValuePtr ptr)
{
    DECLARE_LOCAL_VALUE(ptr);
    return value->Uint32Value(local_ctx).ToChecked();
}

ValueBigInt Value2BigInt(ValuePtr ptr)
{
    DECLARE_LOCAL_VALUE(ptr);
    Local<BigInt> bint;
    if (!value->ToBigInt(local_ctx).ToLocal(&bint))
    {
        return {nullptr, 0};
    }

    int word_count = bint->WordCount();
    int sign_bit = 0;
    uint64_t *words = (uint64_t *)malloc(sizeof(uint64_t) * word_count);
    bint->ToWordsArray(&sign_bit, &word_count, words);
    ValueBigInt rtn = {words, word_count, sign_bit};
    return rtn;
}

RValue Value2Object(ValuePtr ptr)
{
    DECLARE_LOCAL_VALUE(ptr);
    RValue rtn;
    Local<Object> obj;
    if (!value->ToObject(local_ctx).ToLocal(&obj))
    {
        rtn.error = ExceptionError(try_catch, iso, local_ctx);
        return rtn;
    }
    ValuePtr new_val;
    new_val->iso = iso;
    new_val->ctx = ctx;
    new_val->instance = Persistent<Value, CopyablePersistentTraits<Value>>(iso, obj);
    rtn.value = new_val;
    rtn.ok = true;
    return rtn;
}

int ValueSameValue(ValuePtr val1, ValuePtr val2)
{
    Isolate *iso = val1->iso;
    DECLARE_ISOLATE_SCOPE(iso);
    Local<Value> value1 = val1->instance.Get(iso);
    Local<Value> value2 = val2->instance.Get(iso);
    return value1->SameValue(value2);
}

CStr LangVersion()
{
    return V8::GetVersion();
}

CStr Mask()
{
    return "REMJS";
}