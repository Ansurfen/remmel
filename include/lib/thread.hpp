#ifndef __REMMEL_THREAD__
#define __REMMEL_THREAD__

#include "constant.hpp"

namespace remmel
{
    enum class REM_TASK_TYPE
    {
        TRAP,        // wrap into kernel to exec code
        WRITE,       // write bplus tree to disk
        READ,        // read data from disk to update mem
        INTERPRETER, // interpreter sql to IR
        CONN,        // hanlder conn from client
    };

    class Task
    {
    private:
        REM_TASK_TYPE type;

    public:
        Task(REM_TASK_TYPE t) : type(t){};
        ~Task();
        void process();
    };

    class ThreadPool
    {
    private:
        Vec<Thread *> works;
        Cond_v cv;
        Mutex mut;
        Que<Task *> tasks;
        bool running;

        Thread *addWorker();
        void work();

    public:
        ThreadPool(int cnt = 10);
        ~ThreadPool();
        void AddTask(Task *);
        void AddTaskWithTx(Task *);
        void AddWorkers(int);
        void Start();
    };
}

#endif