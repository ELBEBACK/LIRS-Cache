#include <iostream>
#include <cassert>
#include "lirs.hpp"

static int slowgetpage(int key) { return key; }

int main() {
    int hits = 0;
    int n;
    size_t m;

    std::cout << "Enter cache capacity: ";
    std::cin >> m;

    std::cout << "Enter the number of queries: ";
    std::cin >> n;

    assert(std::cin.good());

    caches::cache_t<int, int> cache{m};
    
    for (int i = 0; i < n; ++i) {
        int query;
        std::cin >> query;
        assert(std::cin.good());
        if (cache.lookup_update(query, slowgetpage)) 
            hits += 1;
    } 

    std::cout << hits << std::endl;

    return 0;
}