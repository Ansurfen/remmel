#include "../../include/ffi/js/cooling.hpp"

RError ExceptionError(TryCatch &try_catch, IsolatePtr iso, Local<Context> ctx)
{
    HandleScope handle_scope(iso);
    RError err;
    if (try_catch.HasTerminated())
    {
        err.msg = FStr("ExecutionTerminated: script execution has been terminated").data();
        return err;
    }
    String::Utf8Value exception(iso, try_catch.Exception());
    err.msg = FStr(*exception, exception.length()).data();
    Local<Message> msg = try_catch.Message();
    if (!msg.IsEmpty())
    {
        String::Utf8Value origin(iso, msg->GetScriptOrigin().ResourceName());
        std::ostringstream sb;
        sb << *origin;
        Maybe<int> line = try_catch.Message()->GetLineNumber(ctx);
        if (line.IsJust())
        {
            sb << ":" << line.ToChecked();
        }
        Maybe<int> start = try_catch.Message()->GetStartColumn(ctx);
        if (start.IsJust())
        {
            sb << ":"
               << start.ToChecked() + 1; // + 1 to match output from stack trace
        }
        err.location = FStr(sb.str()).data();
    }
    Local<Value> mstack;
    if (try_catch.StackTrace(ctx).ToLocal(&mstack))
    {
        String::Utf8Value stack(iso, mstack);
        err.stack = FStr(*stack, stack.length()).data();
    }
    return err;
}

ValuePtr IsolateThrowException(IsolatePtr iso, ValuePtr value)
{
    DECLARE_ISOLATE_SCOPE(iso);
    ContextPtr ctx = value->ctx;
    Local<Value> throw_ret_val = iso->ThrowException(value->instance.Get(iso));
    ValuePtr new_val;
    new_val->iso = iso;
    new_val->ctx = ctx;
    new_val->instance = Persistent<Value, CopyablePersistentTraits<Value>>(iso, throw_ret_val);
    return new_val;
}