#ifndef __REMMEL_TIRE__
#define __REMMEL_TIRE__

#include "constant.hpp"

namespace remmel
{
#define TIRE_CHILDREN_NUM 26
    class Tire
    {
    private:
        bool isWord;
        Tire *children[TIRE_CHILDREN_NUM];

    public:
        Tire();
        ~Tire();
        void Insert(FStr);
        void Delete(FStr);
        bool Find(FStr);
        bool operator[](FStr);
    };

    class ITire // iterable tire
    {
    private:
        Tire *tire;
        Vec<FStr> words; // require a skiplist to enhance speed

    public:
        ITire();
        ~ITire();
        void Insert(FStr);
        void Delete(FStr);
        bool Find(FStr);
        bool operator[](FStr);
        Vec<FStr> toString(bool isSort = true);
    };

    template <class T>
    class TTire // template tire
    {
    private:
        bool isWord;
        TTire *children[TIRE_CHILDREN_NUM];
        T data;

    public:
        TTire();
        ~TTire();
        void Insert(FStr, T);
        void Delete(FStr);
        bool Find(FStr);
        T Get(FStr);
        T operator[](FStr);
    };
}

#endif