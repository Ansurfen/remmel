#ifndef __REMMEL_LIB__
#define __REMMEL_LIB__

#include "libc.h"
#include <vector>
#include <map>
#include <unordered_map>
#include <string_view>
#include <string>
#include <iostream>
#include <fstream>
#include <tuple>
#include <queue>
#include <mutex>
#include <utility>
#include <functional>
#include <thread>
#include <condition_variable>
#include <algorithm>
#include <csignal>
#include <sstream>
#include <deque>
#include <stack>
#include <stdexcept>

#ifdef _WIN32

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <WinSock2.h>
#pragma comment(lib, "Ws2_32.lib")
#include <Mswsock.h>
#pragma comment(lib, "Mswsock.lib")

#elif __linux__

#include <sys/epoll.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#elif __APPLE__

#include <unistd.h>
#include <sys/event.h>

#endif

#endif