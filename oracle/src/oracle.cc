#include <iostream>
#include <cassert>
#include "oracle.hpp"

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

    std::vector<int> queries;
    for (int i = 0, query; i < n; ++i) {
        std::cin >> query;
        assert(std::cin.good());
        queries.push_back(query);
    }

    oracle::cache_t<int, int> cache{m, queries};

    for (int i = 0; i < queries.size(); ++i) {
        if (cache.lookup_update(queries[i], slowgetpage)) 
            hits += 1;
    }

    std::cout << hits << std::endl;
    
    return 0;
}