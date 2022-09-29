#include "../include/lib/mem.hpp"

using namespace remmel;

template <size_t ObjectSize, size_t ObjectNums>
remmel::MemPool<ObjectSize, ObjectNums>::MemPool()
{
    this->free_node = nullptr;
    this->block_head = nullptr;
}

template <size_t ObjectSize, size_t ObjectNums>
remmel::MemPool<ObjectSize, ObjectNums>::~MemPool()
{
    Block *p;
    while (block_head)
    {
        p = block_head->next;
        delete block_head;
        block_head = p;
    }
}

template <size_t ObjectSize, size_t ObjectNums>
void *remmel::MemPool<ObjectSize, ObjectNums>::malloc()
{
    if (!this->free_node)
    {
        Block *new_block = new Block;
        new_block->next = nullptr;
        this->free_node = &(new_block->node[0]);
        for (size_t i = 1; i < ObjectNums; i++)
            new_block->node[i - 1].next = &(new_block->node[i]);
        new_block->node[ObjectNums - 1].next = nullptr;
        if (!this->block_head)
            this->block_head = new_block;
        else
        {
            this->block_head->next = new_block;
            this->block_head = new_block;
        }
    }
    Node *new_node = this->free_node;
    this->free_node = this->free_node->next;
    return new_node;
}

template <size_t ObjectSize, size_t ObjectNums>
void remmel::MemPool<ObjectSize, ObjectNums>::free(void *ptr)
{
    Node *node = reinterpret_cast<Node *>(ptr);
    node->next = this->free_node;
    this->free_node = node;
}