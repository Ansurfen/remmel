#ifndef __REMMEL_SIGNAL__
#define __REMMEL_SIGNAL__

#include "../lib/libr.hpp"

namespace remmel
{
#define GetSignals Signals::_GetSignals()

    void shutdown(int);

    class Signals
    {
    private:
        static Signals *instance;

    public:
        Signals();
        ~Signals();
        static Signals *_GetSignals();
        void Raise(int);
    };

    Signals *Signals::instance = new Signals;
}

#endif