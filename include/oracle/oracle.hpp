#pragma once

#include <deque>
#include <vector>
#include <unordered_map>
#include <iterator>


namespace oracle {

template <typename KeyT, typename T>
class cache_t{

    size_t cache_capacity_;

    using TimelineHash = typename std::unordered_map<KeyT, std::deque<int>>;

    TimelineHash hash_;
    std::unordered_map<KeyT, T> cache_;

    using HashIt = typename TimelineHash::iterator;
    using CacheIt = typename std::unordered_map<KeyT, T>::iterator;

private:

    auto furthest_next() const {
        int furthest_dist = 0;
        auto result = cache_.end();

        for (auto i = cache_.begin(); i != cache_.end(); ++i) {
            auto tmp = hash_.find(i->first);
            if (tmp->second.empty())
                return i;

            if ((tmp->second).front() > furthest_dist) {
                furthest_dist = (tmp->second).front();
                result = i;
            }
        }

        return result;
    }


public:

    template <typename Container>
    cache_t(size_t sz, const Container &incoming_queries) : cache_capacity_(sz) {
        
        for (size_t i = 0; i < incoming_queries.size(); ++i) {
            hash_[incoming_queries[i]].push_back(i);
        }

    }


    template <typename F> bool lookup_update(const KeyT &key, F slowgetpage) {
        
        CacheIt hitCache = cache_.find(key);
        HashIt hitHash = hash_.find(key);

        int queryIt = hitHash->second.front();
        hitHash->second.pop_front();

        if (hitCache == cache_.end()) {
            
            if (cache_.size() < cache_capacity_) {
                cache_.emplace(hitHash->first, slowgetpage(key));
                return false;
            }

            if (hitHash->second.empty()) 
                return false;
            
            auto evicteeCache = furthest_next();
            HashIt evicteeHash = hash_.find(evicteeCache->first);

            if (evicteeHash->second.empty())
                return false;
            
            if (evicteeHash->second.front() < hitHash->second.front())
                return false;

            cache_.erase(evicteeCache);
            cache_.emplace(hitHash->first, slowgetpage(key));
            return false;

        }

        return true;
    }


};

}