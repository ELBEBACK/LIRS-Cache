#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <gtest/gtest.h>
#include "oracle.hpp"

static int slowgetpage(int key) { return key; }
int get_cache_hits(oracle::cache_t<int, int> &cache, std::vector<int> &data);


TEST(CacheTest, AllUniqueQueries)
{
    std::vector<int> data = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    oracle::cache_t<int, int> cache {4, data};

    EXPECT_EQ(get_cache_hits(cache, data), 0);
}


TEST(CacheTest, EvictionOfLatest)
{
    std::vector<int> data = {1, 2, 3, 4, 5, 2, 3, 4, 1, 4, 6, 7};
    oracle::cache_t<int, int> cache {3, data};

    EXPECT_EQ(get_cache_hits(cache, data), 4);
}


TEST(CacheTest, StayingCalmMinimumCapacity)
{
    std::vector<int> data = {1, 2, 1, 2, 1, 2, 1, 2};
    oracle::cache_t<int, int> cache {1, data};

    EXPECT_EQ(get_cache_hits(cache, data), 3);
}


TEST(CacheTest, StayingCalmGeneralCase)
{
    std::vector<int> data = {1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4};
    oracle::cache_t<int, int> cache {3, data};

    EXPECT_EQ(get_cache_hits(cache, data), 6);
}


int get_cache_hits(oracle::cache_t<int, int> &cache, std::vector<int> &data) {

    int hits = 0;
    for(int data_elem : data) {
        hits += cache.lookup_update(data_elem, slowgetpage);
    }

    return hits;
}