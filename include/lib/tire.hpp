#ifndef __REMMEL_TIRE__
#define __REMMEL_TIRE__

#include "constant.hpp"

namespace remmel
{
    class Tire
    {
#define M 26

    private:
        bool isWord;
        Tire *children[M];

    public:
        Tire();
        ~Tire();
        void Insert(FStr);
        void Delete(FStr);
        bool Find(FStr);
    };
}

#endif