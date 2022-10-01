#ifndef __REMMEL_CONSTANT__
#define __REMMEL_CONSTANT__

#include "libr.hpp"

#define bits_t uint8_t
#define bitstream bits_t *

#define INT_LEN sizeof(int)
#define SHORT_LEN sizeof(short)
#define LONG_LEN sizeof(long)
#define LLONG_LEN sizeof(long long)
#define FLOAT_LEN sizeof(float)
#define DOUBLE_LEN sizeof(double)
#define CHAR_LEN sizeof(char)
#define BOOL_LEN CHAR_LEN
#define PTR_LEN sizeof(void *)

#define HashMap std::unordered_map
#define Map std::map
#define Vec std::vector
#define Str std::string
#define FStr std::string_view // the faster string
#define Que std::queue
#define Tuple std::tuple
#define Deque std::deque
#define Stack std::stack
#define Pair std::pair

#define SStream std::stringstream
#define Ifstream std::ifstream
#define Ofstream std::ofstream

#define Thread std::thread
#define Atomic std::atomic

#define Cout std::cout
#define Endl std::endl

#define Mutex std::mutex
#define UniLock std::unique_lock

#define Cond_t std::conditional_t
#define Cond_v std::condition_variable
#define Enable_if_t std::enable_if_t

#define Swap std::swap

#define Runtime_error std::runtime_error

#endif