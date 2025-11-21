#include <iostream>
#include <cassert>
#include "oracle.hpp"

static int slowgetpage(int key) { return key; }

int main() {
    
    int n;
    size_t m;
    
    std::cin >> m;
    if ( !std::cin.good() || m <= 0 )  {
        std::cerr << "Invalid input: positive integer expected for cache capacity\n";
        return EXIT_FAILURE;
    }

    std::cin >> n;
    if ( !std::cin.good() || n <= 0 )  {
        std::cerr << "Invalid input: positive integer expected for a number of queries\n";
        return EXIT_FAILURE;
    }

    std::vector<int> queries;
    for (int i = 0, query; i < n; ++i) {
        
        std::cin >> query;
        if ( !std::cin.good() || query <= 0 )  {
            std::cerr << "Invalid input: positive integers expected in a sequence of queries\n";
            return EXIT_FAILURE;
        }
        queries.push_back(query);
    
    }

    oracle::cache_t<int, int> cache{m, queries};

    int hits = 0;
    for (int i = 0; i < queries.size(); ++i) {
        hits += cache.lookup_update(queries[i], slowgetpage);
    }

    std::cout << hits << std::endl;
    
    return 0;
}