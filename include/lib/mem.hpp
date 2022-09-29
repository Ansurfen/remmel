#ifndef __REMMEL_MEM__
#define __REMMEL_MEM__

#include "constant.hpp"

namespace remmel
{
    template <size_t ObjectSize, size_t ObjectNums = 4>
    class MemPool
    {
    private:
        struct Node
        {
            bits_t data[ObjectSize];
            struct Node *next;
        };

        struct Block
        {
            Node node[ObjectNums];
            struct Block *next;
        };

        Node *free_node;
        Block *block_head;
        Mutex mut;

    public:
        MemPool();
        ~MemPool();
        void *malloc();
        void free(void *);
    };
}

#endif