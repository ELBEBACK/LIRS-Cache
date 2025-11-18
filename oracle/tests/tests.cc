#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <gtest/gtest.h>
#include "../include/oracle.hpp"

static int slowgetpage(int key) { return key; }

TEST(CacheTest, TEST1)
{
    std::vector<int> data = {1, 2, 3, 1, 2, 4, 1, 2, 5, 1, 2, 6, 1, 2, 3, 1, 2, 4, 1, 2};
    oracle::cache_t<int, int> cache {3, data};

    int hits = 0;
    for(int data_elem : data) {
        if (cache.lookup_update(data_elem, slowgetpage))
            ++hits;
    }

    EXPECT_EQ(hits, 13);
}

TEST(CacheTest, TEST2)
{
    std::vector<int> data = {1, 2, 3, 4, 5, 1, 2, 3, 6, 7, 1, 2, 3, 8, 9, 1, 2, 3, 10, 11};
    oracle::cache_t<int, int> cache {5, data};

    int hits = 0;
    for(int data_elem : data) {
        if (cache.lookup_update(data_elem, slowgetpage))
            ++hits;
    }

    EXPECT_EQ(hits, 9);
}

TEST(CacheTest, TEST3)
{
    std::vector<int> data = {1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 9, 10, 1, 2, 11, 12, 1, 2, 13, 14};
    oracle::cache_t<int, int> cache {10, data};

    int hits = 0;
    for(int data_elem : data) {
        if (cache.lookup_update(data_elem, slowgetpage))
            ++hits;
    }

    EXPECT_EQ(hits, 6);
}

TEST(CacheTest, TEST4)
{
    std::vector<int> data = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 1, 2, 14, 15, 1, 2, 16};
    oracle::cache_t<int, int> cache {15, data};

    int hits = 0;
    for(int data_elem : data) {
        if (cache.lookup_update(data_elem, slowgetpage))
            ++hits;
    }

    EXPECT_EQ(hits, 4);
}

TEST(CacheTest, TEST5)
{
    std::vector<int> data = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 1, 2};
    oracle::cache_t<int, int> cache {20, data};

    int hits = 0;
    for(int data_elem : data) {
        if (cache.lookup_update(data_elem, slowgetpage))
            ++hits;
    }

    EXPECT_EQ(hits, 2);
}

TEST(CacheTest, TEST6)
{
    std::vector<int> data = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 1, 2, 3, 4, 5};
    oracle::cache_t<int, int> cache {100, data};

    int hits = 0;
    for(int data_elem : data) {
        if (cache.lookup_update(data_elem, slowgetpage))
            ++hits;
    }

    EXPECT_EQ(hits, 5);
}

TEST(CacheTest, TEST7)
{
    std::vector<int> data = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    oracle::cache_t<int, int> cache {15, data};

    int hits = 0;
    for(int data_elem : data) {
        if (cache.lookup_update(data_elem, slowgetpage))
            ++hits;
    }

    EXPECT_EQ(hits, 10);
}

TEST(CacheTest, TEST8)
{
    std::vector<int> data = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20};
    oracle::cache_t<int, int> cache {3, data};

    int hits = 0;
    for(int data_elem : data) {
        if (cache.lookup_update(data_elem, slowgetpage))
            ++hits;
    }

    EXPECT_EQ(hits, 0);
}

TEST(CacheTest, TEST9)
{
    std::vector<int> data = {1, 2, 3, 4, 2, 3, 1, 5, 3, 1, 2, 6, 1, 3, 2, 7, 2, 1, 3, 8};
    oracle::cache_t<int, int> cache {4, data};

    int hits = 0;
    for(int data_elem : data) {
        if (cache.lookup_update(data_elem, slowgetpage))
            ++hits;
    }

    EXPECT_EQ(hits, 12);
}


int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}