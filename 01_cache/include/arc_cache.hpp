#ifndef ARC_CAHCE_H
#define ARC_CAHCE_H

#include <algorithm>
#include <iostream>
#include <list>
#include <unordered_map>
#include "cache.hpp"
#include "debug.hpp"

class ARCCache final : public Cache_I {
    using size_t = std::size_t;

   private:
    // Cached entries, referenced only once
    std::list<int> cached_ref_once;

    // Cached entries, referenced at least twice
    std::list<int> cached_ref_mult;

    // "Ghost" entries, referenced once some time in the past, but evicted from cache
    std::list<int> ghost_ref_once;

    // "Ghost" entries, referenced several times in the past, but evicted from cache
    std::list<int> ghost_ref_mult;

    size_t capacity;
    size_t adapt_param;

    struct list_info {
        size_t list_num;
        std::list<int>::iterator iter;
    };

    enum LIST_NUMBER {
        T1 = 0,
        T2 = 1,
        B1 = 2,
        B2 = 3,
    };

    std::unordered_map<int, list_info> elem_to_iter;

    std::list<int>::iterator find(std::list<int>& where, int elem) {
        return std::find(where.begin(), where.end(), elem);
    }

    void replace(size_t p, bool in_b2);

    // These cases are taken from paper "ARC: A SELF-TUNING, LOW OVERHEAD REPLACEMENT CACHE"
    // CASE I
    bool case_hit(int elem, list_info& info);

    // CASE II
    bool case_b1(list_info& info);

    // CASE III
    bool case_b2(list_info& info);

    // CASE IV
    bool case_miss(int elem);
    void case_l1_full(int elem);
    void case_l1_less(int elem);

   public:
    ARCCache(int c, slow_get_page_t get_page)
        : Cache_I(get_page), capacity(c), adapt_param(0), elem_to_iter() {}

    bool LookupUpdate(int elem) override;

    int FetchElem([[maybe_unused]] int elem) override { return get_page_(elem); }
};

#endif  // ARC_CAHCE_H
