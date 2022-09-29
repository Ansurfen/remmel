#ifndef __REMMEL_PACKET__
#define __REMMEL_PACKET__

#include "../lib/constant.hpp"
#include "../lib/thread.hpp"
#include "../lib/debug.hpp"

namespace remmel
{
    static HashMap<FStr, REM_TASK_TYPE> events = {
        {"000", REM_TASK_TYPE::TRAP},
        {"001", REM_TASK_TYPE::WRITE},
        {"010", REM_TASK_TYPE::READ},
        {"100", REM_TASK_TYPE::INTERPRETER},
        {"101", REM_TASK_TYPE::CONN},
    };

    class Packet
    {
    private:
        FStr data;
        REM_TASK_TYPE type;

    public:
        Packet(FStr);
        ~Packet();
        void Wrap(REM_TASK_TYPE, FStr);
    };
}

#endif