#include "../../include/ffi/js/dashboard.hpp"

CPUProfilerPtr NewCPUProfiler(IsolatePtr iso)
{
    Locker locker(iso);
    Isolate::Scope isolate_scope(iso);
    HandleScope handle_scope(iso);
    CPUProfilerPtr c = new CPUProfiler;
    c->iso = iso;
    c->ptr = CpuProfiler::New(iso);
    return c;
}

void CPUProfilerDispose(CPUProfilerPtr profiler)
{
    if (profiler->ptr == nullptr)
        return;
    profiler->ptr->Dispose();
    delete profiler;
}

void CPUProfilerStartProfiling(CPUProfilerPtr profiler, CStr title)
{
    if (profiler->iso == nullptr)
        return;
    Locker locker(profiler->iso);
    Isolate::Scope isolate_scope(profiler->iso);
    HandleScope handle_scope(profiler->iso);

    Local<String> title_str =
        String::NewFromUtf8(profiler->iso, title, NewStringType::kNormal)
            .ToLocalChecked();
    profiler->ptr->StartProfiling(title_str);
}

CPUProfileNodePtr NewCPUProfileNode(const CpuProfileNodePtr ptr)
{
    int count = ptr->GetChildrenCount();
    CPUProfileNodePtr *children = new CPUProfileNodePtr[count];
    for (int i = 0; i < count; ++i)
        children[i] = NewCPUProfileNode(ptr->GetChild(i));
    CPUProfileNodePtr root = new CPUProfileNode{
        ptr,
        ptr->GetScriptResourceNameStr(),
        ptr->GetFunctionNameStr(),
        ptr->GetLineNumber(),
        ptr->GetColumnNumber(),
        count,
        children,
    };
    return root;
}

CPUProfilePtr CPUProfilerStopProfiling(CPUProfilerPtr profiler, CStr title)
{
    if (profiler->iso == nullptr)
        return nullptr;
    Locker locker(profiler->iso);
    Isolate::Scope isolate_scope(profiler->iso);
    HandleScope handle_scope(profiler->iso);
    Local<String> title_str =
        String::NewFromUtf8(profiler->iso, title, NewStringType::kNormal)
            .ToLocalChecked();
    CPUProfilePtr profile = new CPUProfile;
    profile->ptr = profiler->ptr->StopProfiling(title_str);
    Local<String> str = profile->ptr->GetTitle();
    String::Utf8Value t(profiler->iso, str);
    profile->title = FStr(*t, t.length()).data();
    CPUProfileNodePtr root = NewCPUProfileNode(profile->ptr->GetTopDownRoot());
    profile->root = root;
    profile->startTime = profile->ptr->GetStartTime();
    profile->endTime = profile->ptr->GetEndTime();
    return profile;
}

void CPUProfileNodeDelete(CPUProfileNodePtr node)
{
    for (int i = 0; i < node->childrenCount; ++i)
        CPUProfileNodeDelete(node->children[i]);
    delete[] node->children;
    delete node;
}

void CPUProfileDelete(CPUProfilePtr profile)
{
    if (profile->ptr == nullptr)
        return;
    profile->ptr->Delete();
    free((void *)profile->title);
    CPUProfileNodeDelete(profile->root);
    delete profile;
}

IsolateHStatistics IsolationGetHeapStatistics(IsolatePtr iso)
{
    if (iso == nullptr)
        return IsolateHStatistics{0};
    v8::HeapStatistics hs;
    iso->GetHeapStatistics(&hs);
    return IsolateHStatistics{hs.total_heap_size(),
                              hs.total_heap_size_executable(),
                              hs.total_physical_size(),
                              hs.total_available_size(),
                              hs.used_heap_size(),
                              hs.heap_size_limit(),
                              hs.malloced_memory(),
                              hs.external_memory(),
                              hs.peak_malloced_memory(),
                              hs.number_of_native_contexts(),
                              hs.number_of_detached_contexts()};
}