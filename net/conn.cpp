#include "../include/net/conn.hpp"

using namespace remmel;

Conn::Conn(const char *host, uint16_t port)
{
#ifdef _WIN32
    this->instance = new WinConn(host, port);
#elif __linux__
    this->instance = new LinuxConn(host, port);
#elif __APPLE__
    this->instance = new AppleConn(host, port);
#endif
}

Conn::~Conn()
{
}

Packet *remmel::Conn::await()
{
    return this->instance->await();
}

#ifdef _WIN32

ASYNC_IO_HANDLE::ASYNC_IO_HANDLE(SOCKET sock, IO_EVENT event)
{
    memset(this, 0, sizeof(ASYNC_IO_HANDLE));
    this->event = event;
    this->sock = sock;
    this->buf.buf = this->bitBuf;
    this->buf.len = sizeof(this->bitBuf);
    this->dwBytesRecved = 0;
    this->dwFlag = 0;
}

WinConn::WinConn(const char *host, u_short port)
{
    WSADATA wsaData;
    int err = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (err != 0)
        FATAL("fail to init server");
    if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2)
    {
        FATAL("fail to init server");
        CLOSE_SERVER();
        return;
    }
    this->sock = NewSocket();
    if (this->sock == SOCKET_ERROR)
        FATAL("fail to create socket");
    else
        INFO("success to create socket");
    SockInfo si;
    si.sin_family = AF_INET;
    si.sin_addr.S_un.S_addr = FormatAddr(host);
    si.sin_port = htons(port);
    int ret = bind(this->sock, (sockaddr *)&si, sizeof(si));
    if (ret == SOCKET_ERROR)
        FATAL("fail to bind port");
    else
        INFO("success to bind port");
    ret = listen(this->sock, SOMAXCONN);
    if (ret == SOCKET_ERROR)
        FATAL("fail to listen");
    else
        INFO("success to listen");
    ULONG uKey = 0;
    this->icop = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, NULL, 0);
    HANDLE bRet = CreateIoCompletionPort((HANDLE)this->sock, this->icop, NULL, 0);
    this->postAccept();
}

WinConn::~WinConn()
{
    CLOSE_SERVER();
}

void WinConn::postAccept()
{
    SOCKET sock = NewSocket();
    HANDLE hd = CreateIoCompletionPort((HANDLE)sock, this->icop, NULL, 0);
    char buf[MAXBYTE] = {0};
    DWORD dwRecved = 0;
    ASYNC_HANDLE *ahd = new ASYNC_HANDLE(sock, IO_EVENT::IO_ACCEPT);
    CreateAsyncAccept(this->sock, sock, buf, 0, sizeof(sockaddr) + 16, sizeof(sockaddr) + 16, &dwRecved, ahd);
}

void WinConn::postRecv(SOCKET sock)
{
    ASYNC_HANDLE *ahd = new ASYNC_HANDLE(sock, IO_EVENT::IO_RECV);
    CreateAsyncRecv(sock, &ahd->buf, 1, &ahd->dwBytesRecved, &ahd->dwFlag, ahd, NULL);
}

void WinConn::postSend(SOCKET sock)
{
    ASYNC_HANDLE *ahd = new ASYNC_HANDLE(sock, IO_EVENT::IO_SEND);
    CreateAsyncSend(sock, &ahd->buf, 1, &ahd->dwBytesRecved, ahd->dwFlag, ahd, NULL);
}

Packet *WinConn::await()
{
    DWORD dwBytesTranfered = 0;
    ULONG_PTR uKey;
    LPOVERLAPPED pOv = NULL;
    bool ok = GetQueuedCompletionStatus(
        this->icop,
        &dwBytesTranfered,
        &uKey,
        &pOv,
        INFINITE);
    if (!ok)
        return;
    ASYNC_HANDLE *ahd = (ASYNC_HANDLE *)pOv;
    switch (ahd->event)
    {
    case IO_EVENT::IO_ACCEPT:
        this->postAccept();
        std::cout << "a new conn..." << std::endl;
        this->postRecv(ahd->sock);
        break;
    case IO_EVENT::IO_RECV:
        return new Packet(ahd->bitBuf);
    case IO_EVENT::IO_SEND:
        std::cout << "msg is sent" << std::endl;
        break;
    default:
        break;
    }
    return nullptr;
}

void WinConn::close()
{
    CLOSE_SERVER();
}

#elif __linux__

#elif __APPLE__

#endif