#include "../../include/store/mlsm/memtable.hpp"

using namespace remmel;

MemTable::MemTable() : tire(new TTire<FStr>) {}

MemTable::~MemTable()
{
    delete this->tire;
}

void MemTable::Insert(FStr k, FStr v)
{
    this->tire->Insert(k, v);
    this->words.emplace_back(k);
}

void MemTable::Delete(FStr k)
{
    this->tire->Delete(k);
    Vec<FStr>::iterator it = find(this->words.begin(), this->words.end(), k);
    this->words.erase(it);
}

Vec<FStr> MemTable::toString(bool isSort)
{
    if (isSort)
        Sort(this->words.begin(), this->words.end());
    return this->words;
}