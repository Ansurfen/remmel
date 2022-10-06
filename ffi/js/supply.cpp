#include "../../include/ffi/js/supply.hpp"

void TemplateFreeWrapper(TemplatePtr tmpl)
{
    tmpl->instance.Empty();
    delete tmpl;
}

void TemplateSetValue(TemplatePtr ptr, CStr name, ValuePtr val, int attributes)
{
    DECLARE_LOCAL_TEMPLATE(ptr);
    Local<String> prop_name =
        String::NewFromUtf8(iso, name, NewStringType::kNormal).ToLocalChecked();
    tmpl->Set(prop_name, val->instance.Get(iso), (PropertyAttribute)attributes);
}

void TemplateSetTemplate(TemplatePtr ptr, CStr name, TemplatePtr obj, int attributes)
{
    DECLARE_LOCAL_TEMPLATE(ptr);
    Local<String> prop_name =
        String::NewFromUtf8(iso, name, NewStringType::kNormal).ToLocalChecked();
    tmpl->Set(prop_name, obj->instance.Get(iso), (PropertyAttribute)attributes);
}

TemplatePtr NewObjectTemplate(IsolatePtr iso)
{
    Locker locker(iso);
    Isolate::Scope isolate_scope(iso);
    HandleScope handle_scope(iso);
    TemplatePtr ot;
    ot->iso = iso;
    ot->instance.Reset(iso, ObjectTemplate::New(iso));
    return ot;
}

RValue ObjectTemplateNewInstance(TemplatePtr ptr, ContextPtr ctx)
{
    DECLARE_LOCAL_TEMPLATE(ptr);
    TryCatch try_catch(iso);
    Local<Context> local_ctx = ctx->instance.Get(iso);
    Context::Scope context_scope(local_ctx);
    RValue rv;
    Local<ObjectTemplate> obj_tmpl = tmpl.As<ObjectTemplate>();
    Local<Object> obj;
    if (!obj_tmpl->NewInstance(local_ctx).ToLocal(&obj))
    {
        rv.error = ExceptionError(try_catch, iso, local_ctx);
        return rv;
    }
    ValuePtr val;
    val->iso = iso;
    val->ctx = ctx;
    val->instance = Persistent<Value, CopyablePersistentTraits<Value>>(iso, obj);
    rv.value = val;
    rv.ok = true;
    return rv;
}

void ObjectTemplateSetInternalFieldCount(TemplatePtr ptr, int field_count)
{
    DECLARE_LOCAL_TEMPLATE(ptr);
    Local<ObjectTemplate> obj_tmpl = tmpl.As<ObjectTemplate>();
    obj_tmpl->SetInternalFieldCount(field_count);
}

int ObjectTemplateInternalFieldCount(TemplatePtr ptr)
{
    DECLARE_LOCAL_TEMPLATE(ptr);
    Local<ObjectTemplate> obj_tmpl = tmpl.As<ObjectTemplate>();
    return obj_tmpl->InternalFieldCount();
}

static void buildCallArguments(IsolatePtr iso, Local<Value> *argv, int argc, ValuePtr args[])
{
    for (int i = 0; i < argc; i++)
        argv[i] = args[i]->instance.Get(iso);
}

RValue FunctionCall(ValuePtr ptr, ValuePtr recv, int argc, ValuePtr args[])
{
    DECLARE_LOCAL_VALUE(ptr);

    RValue rtn;
    Local<Function> fn = Local<Function>::Cast(value);
    Local<Value> *argv = (Local<Value> *)malloc(sizeof(Local<Value>) * argc);
    buildCallArguments(iso, argv, argc, args);
    Local<Value> local_recv = recv->instance.Get(iso);
    Local<Value> result;
    if (!fn->Call(local_ctx, local_recv, argc, argv).ToLocal(&result))
    {
        rtn.error = ExceptionError(try_catch, iso, local_ctx);
        return rtn;
    }
    ValuePtr rtnval;
    rtnval->iso = iso;
    rtnval->ctx = ctx;
    rtnval->instance = Persistent<Value, CopyablePersistentTraits<Value>>(iso, result);
    rtn.value = rtnval;
    rtn.ok = true;
    return rtn;
}
