#include <vector>
#include <ideal_cache.hpp>
#include <arc_cache.hpp>
#include <gtest/gtest.h>

class CacheTest : public testing::Test {
protected:
    CacheTest() {}
};

// ======< Ideal Cache >=======

TEST(CacheTest, Simple) {
    std::vector<int> elements = {1, 2, 2, 3, 4, 1};
    IdealCache ideal{2, elements};
    size_t ideal_hits = 0;

    for (int elem : elements) {
        ideal_hits += ideal.AddElem(elem);
    }

    ASSERT_EQ(ideal_hits, 2);

    ARCCache arc{2};
    size_t arc_hits = 0;

    for (int elem : elements) {
        arc_hits += arc.AddElem(elem);
    }

    ASSERT_EQ(arc_hits, 1);
}

TEST(CacheTest, Medium) {
    std::vector<int> elements = {1, 2, 2, 3, 4, 2, 2, 1, 1, 3, 4};
    IdealCache ideal{2, elements};
    size_t ideal_hits = 0;

    for (int elem : elements) {
        ideal_hits += ideal.AddElem(elem);
    }

    ASSERT_EQ(ideal_hits, 5);

    ARCCache arc{2};
    size_t arc_hits = 0;

    for (int elem : elements) {
        arc_hits += arc.AddElem(elem);
    }

    ASSERT_EQ(arc_hits, 4);
}

TEST(CacheTest, Hard) {
    std::vector<int> elements = {1, 2, 2, 3, 4, 2, 2, 1, 1, 3, 4, 9, 8, 1, 12, 3, 3, 0, 0, 15, 12, 5};
    IdealCache ideal{10, elements};
    size_t ideal_hits = 0;

    for (int elem : elements) {
        ideal_hits += ideal.AddElem(elem);
    }

    ASSERT_EQ(ideal_hits, 12);

    ARCCache arc{10};
    size_t arc_hits = 0;

    for (int elem : elements) {
        arc_hits += arc.AddElem(elem);
    }

    ASSERT_EQ(arc_hits, 12);
}

TEST(CacheTest, Hard1) {
    std::vector<int> elements = {1, 2, 3, 4, 1, 2, 5, 1, 2, 4, 3, 4};
    IdealCache ideal{10, elements};
    size_t ideal_hits = 0;

    for (int elem : elements) {
        ideal_hits += ideal.AddElem(elem);
    }

    ASSERT_EQ(ideal_hits, 7);

    ARCCache arc{10};
    size_t arc_hits = 0;

    for (int elem : elements) {
        arc_hits += arc.AddElem(elem);
    }

    ASSERT_EQ(arc_hits, 7);
}

TEST(CacheTest, Hard2) {
    std::vector<int> elements = {1, 2, 3, 4, 1, 2, 5, 6, 1, 2, 4, 3, 4};
    IdealCache ideal{10, elements};
    size_t ideal_hits = 0;

    for (int elem : elements) {
        ideal_hits += ideal.AddElem(elem);
    }

    ASSERT_EQ(ideal_hits, 7);

    ARCCache arc{10};
    size_t arc_hits = 0;

    for (int elem : elements) {
        arc_hits += arc.AddElem(elem);
    }

    ASSERT_EQ(arc_hits, 7);
}

TEST(CacheTest, Hard3) {
    std::vector<int> elements = {1, 2, 3, 4, 1, 2, 5, 6, 7, 1, 2, 4, 3, 4};
    IdealCache ideal{10, elements};
    size_t ideal_hits = 0;

    for (int elem : elements) {
        ideal_hits += ideal.AddElem(elem);
    }

    ASSERT_EQ(ideal_hits, 7);

    ARCCache arc{10};
    size_t arc_hits = 0;

    for (int elem : elements) {
        arc_hits += arc.AddElem(elem);
    }

    ASSERT_EQ(arc_hits, 7);
}
