#pragma once

#include <list>
#include <unordered_map>
#include <iterator>
#include <algorithm>


namespace caches {

template <typename T, typename KeyT = int> 
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

    
    std::list<KeyT> stackS_;
    std::list<KeyT> queueQ_;

    
    std::unordered_map<KeyT, LIRSBlock> cache_;
    using CacheIt = typename std::unordered_map<KeyT, LIRSBlock>::iterator;

private:

    void alloccate_capacities() {
        
        if (cache_capacity_ <= 3) {
            HIR_capacity_ = 1;
        } else if (cache_capacity_ <= 20) { 
            HIR_capacity_ = 2;
        } else if (cache_capacity_ <= 30) {
            HIR_capacity_ = 3;
        } else if (cache_capacity_ <= 50) {
            HIR_capacity_ = 4; 
        } else {
            HIR_capacity_ = cache_capacity_ / 20; 
        }

    }

    
    bool is_inQueue(KeyT key) const {
        auto it = std::find(queueQ_.begin(), queueQ_.end(), key);
        if (it == queueQ_.end()) return false;
        return true;
    }

    
    CacheIt coldestLIR_toHIR() {
        CacheIt cIt;
        for (auto it = stackS_.rbegin(); it != stackS_.rend(); ++it) {
            cIt = cache_.find(*it);
            if (cIt->second.is_LIR) {
                cIt->second.is_LIR = false;
                break;
            }   
        }
        return cIt;
    }

    
    bool is_full() const {
        return (stackS_.size() < cache_capacity_);
    }


    KeyT getQHead() {
        return *(queueQ_.begin()); 
    }

public:
    
    cache_t(size_t sz) : cache_capacity_(sz) {
        alloccate_capacities();
        LIR_capacity_ = cache_capacity_ - HIR_capacity_;
    }
    

    template <typename F> bool lookup_update(KeyT key, F slowgetpage) {
        
        CacheIt hit = cache_.find(key);
        if (hit == cache_.end()) {

            LIRSBlock newcomer = {};
            newcomer.value = slowgetpage(key);
            
            if (stackS_.size() < LIR_capacity_) {
                newcomer.is_LIR = true;

                newcomer.queueIt = queueQ_.end();
            } else if (!is_full()) {
                newcomer.is_LIR = false;

                queueQ_.emplace_back(key);
                newcomer.queueIt = --(queueQ_.end());
            } else {
                newcomer.is_LIR = false;
                
                stackS_.erase(queueQ_.begin());
                
                queueQ_.emplace_back(key);
                newcomer.queueIt = --(queueQ_.end());
                queueQ_.pop_front();
            }
            
            stackS_.emplace_front(key);
            newcomer.stackIt = stackS_.begin();

            if (!is_full()) {
                cache_.emplace(key, newcomer);
            } else {
                cache_.emplace(cache_.find(getQHead()), key, newcomer);
            }
            return false;
        
        }


        LIRSBlock hitval = hit->second;
        if (is_inQueue(key)) {
            hitval.is_LIR = true;
            queueQ_.erase(hitval.queueIt);
            hitval.queueIt = queueQ_.end();

            auto cooled_down = coldestLIR_toHIR();
            queueQ_.emplace_back(cooled_down->first);
            cooled_down->second.queueIt = --(queueQ_.end());
        } 
        
        stackS_.splice(stackS_.begin(), stackS_, hitval.stackIt);
        hitval.stackIt = stackS_.begin();

        return true;
    }


};

}