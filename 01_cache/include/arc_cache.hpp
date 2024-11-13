#ifndef ARC_CAHCE_H
#define ARC_CAHCE_H

#include <list>
#include <iostream>
#include <algorithm>
#include <unordered_map>
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

    bool case_hit(int elem, list_info& info);
    bool case_b1 (list_info& info);
    bool case_b2 (list_info& info);

  public:
    ARCCache(int c) : t1_(), t2_(), b1_(), b2_(), c_(c), p_(0), elem_to_iter()
    {}

    bool AddElem(int elem) override;
    
    int FetchElem(int elem) override {
        (void)elem;
        return 0;
    }
};

#endif // ARC_CAHCE_H
