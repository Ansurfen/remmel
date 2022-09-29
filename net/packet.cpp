#include "../include/net/packet.hpp"

using namespace remmel;

Packet::Packet(FStr str)
{
    if (str.size() <= 3)
    {
        WARN("invalid request");
        return;
    }
    FStr t = str.substr(0, 3);
    this->Wrap(events[t], str.substr(3, str.size() - 4));
}

void Packet::Wrap(REM_TASK_TYPE type, FStr data)
{
    this->type = type;
    this->data = data;
}