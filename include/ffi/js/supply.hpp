#ifndef __REMMEL_ENGINE_SUPPLY__
#define __REMMEL_ENGINE_SUPPLY__

#include "../../lib/constant.hpp"
#include "cooling.hpp"
#include "glue.hpp"

void TemplateFreeWrapper(TemplatePtr);
void TemplateSetValue(TemplatePtr, CStr, ValuePtr, int);
void TemplateSetTemplate(TemplatePtr, CStr, TemplatePtr, int);

TemplatePtr NewObjectTemplate(IsolatePtr);
RValue ObjectTemplateNewInstance(TemplatePtr, ContextPtr);
void ObjectTemplateSetInternalFieldCount(TemplatePtr, int);
int ObjectTemplateInternalFieldCount(TemplatePtr);

static void buildCallArguments(IsolatePtr, Local<Value> *, int ValuePtr);
RValue FunctionCall(ValuePtr, ValuePtr, int, ValuePtr);

#endif