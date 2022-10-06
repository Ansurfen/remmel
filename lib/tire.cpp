#include "../include/lib/tire.hpp"

using namespace remmel;

Tire::Tire()
{
    this->isWord = false;
    for (uint8_t i = 0; i < TIRE_CHILDREN_NUM; i++)
        this->children[i] = nullptr;
}

Tire::~Tire()
{
    Tire *p = this;
    for (uint8_t i = 0; i < TIRE_CHILDREN_NUM; i++)
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

bool Tire::operator[](FStr word)
{
    return this->Find(word);
}

ITire::ITire() : tire(new Tire) {}

ITire::~ITire()
{
    delete this->tire;
}

void ITire::Insert(FStr word)
{
    this->tire->Insert(word);
    this->words.emplace_back(word);
}

void ITire::Delete(FStr word)
{
    this->tire->Delete(word);
    Vec<FStr>::iterator it = find(this->words.begin(), this->words.end(), word);
    this->words.erase(it);
}

bool ITire::Find(FStr word)
{
    return this->tire->operator[](word);
}

bool ITire::operator[](FStr word)
{
    return this->tire->operator[](word);
}

Vec<FStr> ITire::toString(bool isSort)
{
    if (isSort)
        Sort(this->words.begin(), this->words.end());
    return this->words;
}

template <class T>
TTire<T>::TTire()
{
    this->isWord = false;
    for (uint8_t i = 0; i < M; i++)
        this->children[i] = nullptr;
    this->data = (T)NIL;
}

template <class T>
TTire<T>::~TTire()
{
    TTire *p = this;
    for (uint8_t i = 0; i < M; i++)
    {
        if (p->children[i])
        {
            delete p->children[i];
            p->children[i] = nullptr;
        }
    }
}

template <class T>
void TTire<T>::Insert(FStr word, T data)
{
    TTire *p = this;
    uint32_t loc = 0;
    for (char i : word)
    {
        loc = i - 'a';
        if (!p->children[loc])
            p->children[loc] = new TTire;
        p = p->children[loc];
    }
    p->data = data;
    p->isWord = true;
}

template <class T>
void TTire<T>::Delete(FStr word)
{
    TTire *p = this;
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
    p->data = (T)NIL;
    p->children[loc]->isWord = false;
}

template <class T>
bool TTire<T>::Find(FStr word)
{
    TTire *p = this;
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

template <class T>
T TTire<T>::Get(FStr word)
{
    TTire *p = this;
    uint8_t loc = 0;
    for (char i : word)
    {
        loc = i - 'a';
        if (!p->children[loc])
            return (T)NIL;
        p = p->children[loc];
    }
    return p->data;
}

template <class T>
T TTire<T>::operator[](FStr word)
{
    return this->Get(word);
}