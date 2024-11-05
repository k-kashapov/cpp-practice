#ifndef ARC_CAHCE_H
#define ARC_CAHCE_H

#include <list>
#include <iostream>
#include <algorithm>
#include "cache.hpp"
#include "debug.hpp"

class ARCCache : Cache_I {
using size_t = std::size_t;
  private:
    std::list<int> t1_;
    std::list<int> t2_;
    std::list<int> b1_;
    std::list<int> b2_;
    size_t c_;
    size_t p_;

    std::list<int>::iterator find(std::list<int>& where, int elem) {
        return std::find(where.begin(), where.end(), elem);
    }

    void replace(int xt, size_t p);

    bool case_hit(int elem);
    bool case_b1(int elem);
    bool case_b2(int elem);

  public:
    ARCCache(int c) : t1_(), t2_(), b1_(), b2_(), c_(c), p_(0)
    {}

    bool AddElem(int elem) override;
    
    int FetchElem(int elem) override {
        (void)elem;
        return 0;
    }
};

#endif // ARC_CAHCE_H
