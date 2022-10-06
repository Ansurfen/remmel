#include "../../include/ffi/js/combustor.hpp"

using namespace remmel;

RValue RunScript(ContextPtr ctx, CStr code)
{
    DECLARE_LOCAL_CONTEXT(ctx);
    RValue rv = {false, nullptr, nullptr};
    MaybeLocal<String> rawSource = String::NewFromUtf8(iso, code, NewStringType::kNormal);
    Local<String> source;
    Local<Script> script;
    Local<Value> result;
    if (!rawSource.ToLocal(&source) && !Script::Compile(local_ctx, source).ToLocal(&script) && !script->Run(local_ctx).ToLocal(&result))
    {
        rv.error = ExceptionError(try_catch, iso, local_ctx);
        return rv;
    }
    ValuePtr val;
    val->iso = iso;
    val->ctx = ctx;
    val->instance = Persistent<Value, CopyablePersistentTraits<Value>>(iso, result);
    rv.value = val;
    rv.ok = true;
    return rv;
}

template <JS_TYPE type>
void SetValue(ContextPtr ctx, CStr ident, CStr value)
{
    return SetValue_Helper<type>(ctx, ident, value);
}

template <JS_TYPE type>
Enable_if_t<type == JS_TYPE::JS_NULL> SetValue_Helper(ContextPtr ctx, CStr ident, CStr)
{
    DECLARE_LOCAL_CONTEXT(ctx);
    local_ctx->Global()->Set(local_ctx, String::NewFromUtf8(ident).ToLocalChecked(), Null(iso));
}

template <JS_TYPE type>
Enable_if_t<type == JS_TYPE::JS_UNDEFINED> SetValue_Helper(ContextPtr ctx, CStr ident, CStr)
{
    DECLARE_LOCAL_CONTEXT(ctx);
    local_ctx->Global()->Set(local_ctx, String::NewFromUtf8(ident).ToLocalChecked(), Undefined(iso));
}

template <JS_TYPE type>
Enable_if_t<type == JS_TYPE::JS_INTEGER> SetValue_Helper(ContextPtr ctx, CStr ident, CStr value)
{
    DECLARE_LOCAL_CONTEXT(ctx);
    local_ctx->Global()->Set(local_ctx, String::NewFromUtf8(ident).ToLocalChecked(), Integer::New(iso, std::atoi(value)));
}

template <JS_TYPE type>
Enable_if_t<type == JS_TYPE::JS_BOOLEAN> SetValue_Helper(ContextPtr ctx, CStr ident, CStr value)
{
    DECLARE_LOCAL_CONTEXT(ctx);
    local_ctx->Global()->Set(local_ctx, String::NewFromUtf8(ident).ToLocalChecked(), v8::Boolean::New(iso, !std::atoi(value) ? false : true));
}

template <JS_TYPE type>
Enable_if_t<type == JS_TYPE::JS_NUMBER> SetValue_Helper(ContextPtr ctx, CStr ident, CStr value)
{
    DECLARE_LOCAL_CONTEXT(ctx);
    local_ctx->Global()->Set(local_ctx, String::NewFromUtf8(ident).ToLocalChecked(), Number::New(iso, std::atof(value)));
}

template <JS_TYPE type>
Enable_if_t<type == JS_TYPE::JS_STRING> SetValue_Helper(ContextPtr ctx, CStr ident, CStr value)
{
    DECLARE_LOCAL_CONTEXT(ctx);
    local_ctx->Global()->Set(local_ctx, String::NewFromUtf8(ident).ToLocalChecked(), String::NewFromUtf8(iso, value).ToLocalChecked());
}

template <JS_TYPE type>
Enable_if_t<type == JS_TYPE::JS_BIGINT> SetValue_Helper(ContextPtr ctx, CStr ident, CStr value)
{
    DECLARE_LOCAL_CONTEXT(ctx);
    local_ctx->Global()->Set(local_ctx, String::NewFromUtf8(ident).ToLocalChecked(), BigInt::New(iso, std::atoll(value)));
}

Pair<BitArray, REM_TYPE> get_what(ContextPtr ctx, CStr ident, JS_TYPE t)
{
    RValue rv = RunScript(ctx, ident);
    if (!rv.ok)
    {
    }
    BitArray bits;
    REM_TYPE type = REM_TYPE::EOT;
    switch (t)
    {
    case JS_TYPE::JS_BOOLEAN:
    {
        bits = BitArray(bool(Value2Boolean(rv.value)));
        type = REM_TYPE::BOOL;
    }
    break;
    case JS_TYPE::JS_INTEGER:
    {
        bits = BitArray(int(Value2Integer(rv.value)));
        type = REM_TYPE::LONG;
    }
    break;
    case JS_TYPE::JS_NUMBER:
    {
        bits = BitArray(double(Value2Number(rv.value)));
        type = REM_TYPE::LONG;
    }
    break;
    case JS_TYPE::JS_STRING:
    {
        bits = BitArray(Str(Value2String(rv.value)));
        type = REM_TYPE::STRING;
    }
    break;
    default:
        break;
    }
    return {bits, type};
}
