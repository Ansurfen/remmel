#include "../include/lib/thread.hpp"

using namespace remmel;

ThreadPool::ThreadPool(int cnt)
{
    this->running = false;
    this->AddWorkers(cnt);
}

ThreadPool::~ThreadPool()
{
    {
        UniLock<Mutex> lock(this->mut);
        this->running = false;
        cv.notify_all();
    }
    for (Thread *work : this->works)
    {
        work->join();
        delete work;
    }
    this->works.clear();
}

void ThreadPool::AddWorkers(int cnt)
{
    for (size_t i = 0; i < cnt; i++)
        this->works.emplace_back(this->addWorker());
}

Thread *ThreadPool::addWorker()
{
    return new Thread(std::bind(&ThreadPool::work, this));
}

void ThreadPool::work()
{
    while (this->running)
    {
        std::unique_lock<std::mutex> lock(this->mut);
        this->cv.wait(lock, [this]
                      { return !this->tasks.empty(); });
        if (this->tasks.empty())
            continue;
        else
        {
            Task *task = this->tasks.front();
            this->tasks.pop();
            if (task)
                task->process();
        }
    }
}

void ThreadPool::AddTask(Task *t)
{
    UniLock<Mutex> lock(this->mut);
    this->tasks.push(t);
    cv.notify_one();
}

void ThreadPool::Start()
{
    this->running = true;
}