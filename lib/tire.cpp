#include "../include/lib/tire.hpp"

using namespace remmel;

Tire::Tire()
{
    this->isWord = false;
    for (uint8_t i = 0; i < M; i++)
        this->children[i] = nullptr;
}

Tire::~Tire()
{
    Tire *p = this;
    for (uint8_t i = 0; i < M; i++)
    {
        if (p->children[i])
        {
            delete p->children[i];
            p->children[i] = nullptr;
        }
    }
}

void Tire::Insert(FStr word)
{
    Tire *p = this;
    uint32_t loc = 0;
    for (char i : word)
    {
        loc = i - 'a';
        if (!p->children[loc])
            p->children[loc] = new Tire;
        p = p->children[loc];
    }
    p->isWord = true;
}

void Tire::Delete(FStr word)
{
    Tire *p = this;
    uint8_t loc = 0;
    for (uint8_t i = 0; i < word.size(); i++)
    {
        loc = word[i] - 'a';
        if (p->children[loc] && i == word.size() - 1)
            break;
        if (!p->children[loc])
            return;
        p = p->children[loc];
    }
    p->children[loc]->isWord = false;
}

bool Tire::Find(FStr word)
{
    Tire *p = this;
    uint8_t loc = 0;
    for (char i : word)
    {
        loc = i - 'a';
        if (!p->children[loc])
            return false;
        p = p->children[loc];
    }
    return p->isWord;
}
