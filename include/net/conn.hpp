#ifndef __REMMEL_CONN__
#define __REMMEL_CONN__

#include "../lib/libr.hpp"
#include "../lib/debug.hpp"
#include "packet.hpp"

namespace remmel
{
    class Conn
    {
    private:
#ifdef _WIN32
        WinConn *instance;
#elif __linux__
        LinuxConn *instance;
#elif __APPLE__
        AppleConn *instance;
#endif

    public:
        Conn(const char *, uint16_t);
        ~Conn();
        Packet *await();
    };

#ifdef _WIN32
#define CLOSE_SERVER WSACleanup
#define SockInfo sockaddr_in
#define CreateAsyncAccept AcceptEx
#define CreateAsyncSend WSASend
#define CreateAsyncRecv WSARecv
#define NewSocket() socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)
#define FormatAddr(addr) inet_addr(addr)

    enum class IO_EVENT
    {
        IO_ACCEPT,
        IO_RECV,
        IO_SEND,
    };

    typedef struct ASYNC_IO_HANDLE : public OVERLAPPED
    {
        IO_EVENT event;
        SOCKET sock;
        WSABUF buf;
        char bitBuf[MAXBYTE];
        DWORD dwBytesRecved;
        DWORD dwFlag;
        ASYNC_IO_HANDLE(SOCKET, IO_EVENT);
    } ASYNC_HANDLE;

    class WinConn
    {
    private:
        SOCKET sock;
        HANDLE icop;
        void postAccept();
        void postRecv(SOCKET);
        void postSend(SOCKET);

    public:
        WinConn(const char *, u_short);
        ~WinConn();
        Packet *await();
        void close();
    };
#elif __linux__

#elif __APPLE__

#endif
}

#endif