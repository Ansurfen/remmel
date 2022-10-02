#include "../include/lib/lru.hpp"

using namespace remmel;

template <class K, class V>
LRU_Data<K, V>::LRU_Data(K k, V v) : key(k), val(v) {}

template <typename K, typename V>
LRUCache<K, V>::LRUCache(uint32_t _cap) : cap(_cap) {}

template <class K, class V>
Pair<bool, V> LRUCache<K, V>::get(K k)
{
    if (this->cache_map.find(k) == this->cache_map.end())
        return {false, (V)NIL};
    this->cache_list.splice(cache_list.begin(), this->cache_list, this->cache_map[k]);
    this->cache_map[k] = this->cache_list.begin();
    return {true, this->cache_list[k]->val};
}

template <class K, class V>
void LRUCache<K, V>::set(K k, V v)
{
    if (this->cache_map.find[k] == this->cache_map.end())
    {
        if (this->cache_list.size() == this->cap)
        {
            this->cache_map.erase(this->cache_list.back().key);
            this->cache_list.pop_back();
        }
        this->cache_list.push_front(LRU_Data<K, V>(k, v));
        this->cache_map[k] = this->cache_list.begin();
    }
    else
    {
        this->cache_map[k]->val = v;
        this->cache_list.splice(this->cache_list.begin(), this->cache_list, this->cache_map[k]);
        this->cache_map[k] = this->cache_list.begin();
    }
}