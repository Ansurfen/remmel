#ifndef __REMMEL_LRU__
#define __REMMEL_LRU__

#include "constant.hpp"

namespace remmel
{
    template <typename K, typename V>
    struct LRU_Data
    {
        K key;
        V val;
        LRU_Data(K, V);
    };
    template <typename K, typename V>
    class LRUCache
    {
    private:
        uint32_t cap;
        List<LRU_Data<K, V>> cache_list;
        HashMap<K, typename List<LRU_Data<K, V>>::iterator> cache_map;

    public:
        LRUCache(uint32_t);
        ~LRUCache();
        Pair<bool, V> get(K);
        void set(K, V);
    };
}

#endif