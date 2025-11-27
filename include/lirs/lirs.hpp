#pragma once

#include <list>
#include <unordered_map>
#include <iterator>
#include <algorithm>


namespace caches {

template <typename KeyT, typename T> 
class cache_t{

    size_t cache_capacity_;
    size_t HIR_capacity_;
    size_t LIR_capacity_;

    
    struct LIRSBlock {
        T value;
        bool is_LIR;
        typename std::list<KeyT>::iterator stackIt;
        typename std::list<KeyT>::iterator queueIt;

    };

    
    std::list<KeyT> stack_;
    std::list<KeyT> queue_;

    
    std::unordered_map<KeyT, LIRSBlock> cache_;
    using CacheIt = typename std::unordered_map<KeyT, LIRSBlock>::iterator;

private:

    static size_t calcHIR(size_t cache_capacity){
        
        if (cache_capacity <= 3) 
            return 1;
        if (cache_capacity <= 20)  
            return 2;
        if (cache_capacity <= 30) 
            return 3;
        if (cache_capacity <= 50) 
            return 4; 
        return (cache_capacity < 100) ? 5 : cache_capacity / 20;

    }

    
    bool is_inQueue(const KeyT &key) const {
        return std::ranges::contains(queue_, key);
    }

    
    CacheIt coldestLIR_toHIR() {

        for (auto it = stack_.rbegin(); it != stack_.rend(); ++it) {
            auto cIt = cache_.find(*it);
            if (cIt->second.is_LIR) {
                cIt->second.is_LIR = false;
                return cIt;
            }   
        }
        //It is guaranteed that either LIR blocks exist or there are no blocks in stack
        return cache_.end();
    }

    
    bool is_full() const {
        return (stack_.size() == cache_capacity_);
    }


public:
    
    explicit cache_t(size_t sz) : cache_capacity_(sz),
                        HIR_capacity_(calcHIR(sz)), 
                        LIR_capacity_(cache_capacity_ - HIR_capacity_) {}
    

    template <typename F> bool lookup_update(const KeyT &key, F slowgetpage) {
        
        CacheIt hit = cache_.find(key);
        if (hit == cache_.end()) {

            LIRSBlock newcomer = {};
            newcomer.value = slowgetpage(key);
            
            if (is_full()) {
                newcomer.is_LIR = false;
                
                stack_.erase(std::ranges::find(stack_, queue_.front()));
                
                cache_.erase(queue_.front());
                queue_.pop_front();
                queue_.emplace_back(key);
                newcomer.queueIt = std::prev(queue_.end());
            } else if (stack_.size() >= LIR_capacity_){
                newcomer.is_LIR = false;

                queue_.emplace_back(key);
                newcomer.queueIt = std::prev(queue_.end());
            } else {
                newcomer.is_LIR = true;

                newcomer.queueIt = queue_.end();
            }
            
            stack_.emplace_front(key);
            newcomer.stackIt = stack_.begin();

            cache_.emplace(key, newcomer);
            return false;
        
        }


        LIRSBlock& hitval = hit->second;
        if (is_inQueue(key)) {
            auto cooled_down = coldestLIR_toHIR();
            queue_.emplace_back(cooled_down->first);
            cooled_down->second.queueIt = std::prev(queue_.end(), 1);
        
            hitval.is_LIR = true;
            queue_.erase(hitval.queueIt);
            hitval.queueIt = queue_.end();
        } 
        
        stack_.splice(stack_.begin(), stack_, hitval.stackIt);
        hitval.stackIt = stack_.begin();

        return true;
    }


};

}