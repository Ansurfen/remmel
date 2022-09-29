#ifndef __REMMEL_DEBUG__
#define __REMMEL_DEBUG__

#include "time.hpp"

namespace remmel
{
#define RESET "\033[0m"
#define BLACK "\033[30m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
#define WHITE "\033[37m"

#define DEBUG_MODE

#ifdef DEBUG_MODE

#define FATAL(format, ...)                                                                                                                     \
    do                                                                                                                                         \
    {                                                                                                                                          \
        const char *str = strrchr(__FILE__, '\\');                                                                                             \
        str++;                                                                                                                                 \
        Cout << BLACK << CurTime() << RESET << RED << " [FATAL]" << RESET << BLUE << " [" << str << ":" << __LINE__ << "]" << RESET \
             << CYAN << " [" << __FUNCTION__ << "]" << RESET;                                                                                  \
        printf("%s " format " %s \n", BLACK, ##__VA_ARGS__, RESET);                                                                            \
        Cout << BLACK << "This is an automatically generated exception from Remmel." << RESET << Endl;                                         \
        throw;                                                                                                                                 \
    } while (0)

#define INFO(format, ...)                                                                                                                       \
    do                                                                                                                                          \
    {                                                                                                                                           \
        const char *str = strrchr(__FILE__, '\\');                                                                                              \
        str++;                                                                                                                                  \
        Cout << BLACK << CurTime() << RESET << GREEN << " [INFO]" << RESET << BLUE << " [" << str << ":" << __LINE__ << "]" << RESET \
             << CYAN << " [" << __FUNCTION__ << "]" << RESET;                                                                                   \
        printf("%s " format " %s \n", BLACK, ##__VA_ARGS__, RESET);                                                                             \
    } while (0)

#define WARN(format, ...)                                                                                                                        \
    do                                                                                                                                           \
    {                                                                                                                                            \
        const char *str = strrchr(__FILE__, '\\');                                                                                               \
        str++;                                                                                                                                   \
        Cout << BLACK << CurTime() << RESET << YELLOW << " [WARN]" << RESET << BLUE << " [" << str << ":" << __LINE__ << "]" << RESET \
             << CYAN << " [" << __FUNCTION__ << "]" << RESET;                                                                                    \
        printf("%s " format " %s \n", BLACK, ##__VA_ARGS__, RESET);                                                                              \
    } while (0)
#else

#define FATAL(format, ...)
#define INFO(format, ...)
#define WARN(format, ...)

#endif
}

#endif