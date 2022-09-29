#include "../include/internal/signal.hpp"

using namespace remmel;

void shutdown(int signum)
{
}

Signals::Signals()
{
    signal(SIGINT, shutdown);
    signal(SIGILL, shutdown);
    signal(SIGABRT, shutdown);
    signal(SIGTERM, shutdown);
    signal(SIGFPE, shutdown);
    signal(SIGSEGV, shutdown);
}

Signals::~Signals()
{
    delete instance;
}

Signals *Signals::_GetSignals()
{
    return instance;
}

void Signals::Raise(int signum)
{
    raise(signum);
}