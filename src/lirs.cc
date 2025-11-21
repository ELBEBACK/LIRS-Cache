#include <iostream>
#include <cassert>
#include "lirs.hpp"

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

    caches::cache_t<int, int> cache{m};
    
    int hits = 0;
    for (int i = 0, query; i < n; ++i) {
        
        std::cin >> query;
        if ( !std::cin.good() || query <= 0 )  {
            std::cerr << "Invalid input: positive integers expected in a sequence of queries\n";
            return EXIT_FAILURE;
        }
        
        hits += cache.lookup_update(query, slowgetpage);
    } 

    std::cout << hits << std::endl;

    return 0;
}