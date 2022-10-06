// Refer to v8go.h and v8go.cc from https://github.com/rogchap/v8go
// Thank Roger Chapman and the v8go contributors
#ifndef __REMMEL_ENGINE_DASHBOARD__
#define __REMMEL_ENGINE_DASHBOARD__

#include "glue.hpp"
#include "v8/include/v8-profiler.h"

typedef CpuProfiler *CpuProfilerPtr;
typedef CpuProfile *CpuProfilePtr;
typedef const CpuProfileNode *CpuProfileNodePtr;
typedef ScriptCompiler::CachedData *ScriptCompilerCachedDataPtr;

typedef struct
{
    CpuProfilerPtr ptr;
    IsolatePtr iso;
} CPUProfiler, *CPUProfilerPtr;

typedef struct CPUProfileNode
{
    CpuProfileNodePtr ptr;
    CStr scriptResourceName;
    CStr functionName;
    int lineNumber;
    int columnNumber;
    int childrenCount;
    struct CPUProfileNode **children;
} CPUProfileNode, *CPUProfileNodePtr;

typedef struct
{
    CpuProfilePtr ptr;
    CStr title;
    CPUProfileNode *root;
    int64_t startTime;
    int64_t endTime;
} CPUProfile, *CPUProfilePtr;

typedef struct
{
    size_t total_heap_size;
    size_t total_heap_size_executable;
    size_t total_physical_size;
    size_t total_available_size;
    size_t used_heap_size;
    size_t heap_size_limit;
    size_t malloced_memory;
    size_t external_memory;
    size_t peak_malloced_memory;
    size_t number_of_native_contexts;
    size_t number_of_detached_contexts;
} IsolateHStatistics;

CPUProfilerPtr NewCPUProfiler(IsolatePtr);
void CPUProfilerDispose(CPUProfilerPtr);
void CPUProfilerStartProfiling(CPUProfilerPtr, CStr);
CPUProfileNodePtr NewCPUProfileNode(const CpuProfileNodePtr);
CPUProfilePtr CPUProfilerStopProfiling(CPUProfilerPtr, CStr);
void CPUProfileNodeDelete(CPUProfileNodePtr);
void CPUProfileDelete(CPUProfilePtr);
IsolateHStatistics IsolationGetHeapStatistics(IsolatePtr);

#endif