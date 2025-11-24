#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <gtest/gtest.h>
#include "lirs/lirs.hpp"

static int slowgetpage(int key) { return key; }
int get_cache_hits(caches::cache_t<int, int> &cache, std::vector<int> &data);


TEST(LIRS, AllUniqueQueries_HIREvictions)
{
    caches::cache_t<int, int> cache {3};
    std::vector<int> data = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20};

    EXPECT_EQ(get_cache_hits(cache, data), 0);
}


TEST(LIRS, HIR2LIRPromotion)
{
    caches::cache_t<int, int> cache {3};
    std::vector<int> data = {1, 2, 3, 1, 4, 5, 6, 7, 8, 1};

    EXPECT_EQ(get_cache_hits(cache, data), 2);
}


TEST(LIRS, LIRDemotion)
{
    caches::cache_t<int, int> cache {3};
    std::vector<int> data = {1, 2, 3, 1, 2, 4, 4, 5, 6, 7, 8, 1, 2, 4};

    EXPECT_EQ(get_cache_hits(cache, data), 5);
}


TEST(LIRS, Comprehensive_FirstSizeGroup)
{
    caches::cache_t<int, int> cache {3};
    std::vector<int> data = {1, 2, 3, 3, 4, 1, 3, 2, 4};

    EXPECT_EQ(get_cache_hits(cache, data), 3);
}


TEST(LIRS, Comprehensive_SecondSizeGroup)
{
    caches::cache_t<int, int> cache {5};
    std::vector<int> data = {1, 2, 3, 4, 5, 1, 2, 3, 4, 5, 6, 7, 8, 3, 4, 5, 7};

    EXPECT_EQ(get_cache_hits(cache, data), 9);
}


TEST(LIRS, Comprehensive_ThirdSizeGroup)
{
    caches::cache_t<int, int> cache {25};
    std::vector<int> data = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 23, 24, 25, 26, 27, 3, 28, 29, 30};

    EXPECT_EQ(get_cache_hits(cache, data), 4);
}


TEST(LIRS, Comprehensive_FourthSizeGroup)
{
    caches::cache_t<int, int> cache {35};
    std::vector<int> data = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 32, 33, 34, 35, 36, 37, 38, 4, 39, 40};

    EXPECT_EQ(get_cache_hits(cache, data), 5);
}


TEST(LIRS, Comprehensive_FifthSizeGroup)
{
    caches::cache_t<int, int> cache {55};
    std::vector<int> data = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 51, 52, 53, 54, 55, 56, 57, 58, 59, 5, 60};

    EXPECT_EQ(get_cache_hits(cache, data), 6);
}


int get_cache_hits(caches::cache_t<int, int> &cache, std::vector<int> &data) {
    
    int hits = 0;
    for(int data_elem : data) {
        hits += cache.lookup_update(data_elem, slowgetpage);
    }

    return hits;
}