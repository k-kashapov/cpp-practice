#ifndef ARC_CAHCE_H
#define ARC_CAHCE_H

#include "cache.hpp"
#include <list>
#include <iostream>
#include <algorithm>

#ifdef DEBUG
#define debug(x)                                                               \
    do {                                                                       \
        x;                                                                     \
    } while (0)
#else
#define debug(x)                                                               \
    do {                                                                       \
    } while (0)
#endif // DEBUG

using std::size_t;
class ARCCache : Cache_I {
  private:
    std::list<int> t1_;
    std::list<int> t2_;
    std::list<int> b1_;
    std::list<int> b2_;
    int c_;
    int p_ = 0;

    std::list<int>::iterator find(std::list<int>& where, int elem) {
        return std::find(where.begin(), where.end(), elem);
    }

    void replace(int xt, int p) {
        auto found = find(b2_, xt);

        if ((!t1_.empty()) && ( (t1_.size() > p) || ( (found != b2_.end()) && (t1_.size() == p) ) )) {
            b1_.splice(b1_.begin(), t1_, std::prev(t1_.end()));
        } else {
            b2_.splice(b2_.begin(), t2_, std::prev(t2_.end()));
        }
    }

    bool case_hit(int elem) {
        auto found = find(t1_, elem);
        if (found == t1_.end()) {
            found = find(t2_, elem);
        }

        if (found != t2_.end()) {
            // CACHE HIT
            // => move element to MRU (begin) in t2
            t2_.splice(t2_.begin(), t2_, found);
            return true;
        }

        return false;
    }

    bool case_b1(int elem) {
        auto found = find(b1_, elem);
        if (found != b1_.end()) {
            // CASE 2 from paper
            int delta = b1_.size() > b2_.size() ? 1 : b2_.size() / b1_.size();
            p_ = std::min(p_ + delta, c_);
            replace(elem, p_);
            t2_.splice(t2_.begin(), t2_, found);
            return true;
        }

        return false;
    }

    bool case_b2(int elem) {
        auto found = find(b2_, elem);
        if (found != b2_.end()) {
            // CASE 3 from paper
            int delta = b2_.size() > b1_.size() ? 1 : b1_.size() / b2_.size();
            p_ = std::max(p_ - delta, 0);
            replace(elem, p_);
            t2_.splice(t2_.begin(), t2_, found);
            return true;
        }

        return false;
    }

  public:
    ARCCache(int c) : t1_(), t2_(), b1_(), b2_(), c_(c)
    {}

    ~ARCCache()
    {}

    bool AddElem(int elem) {
        if (case_hit(elem)) {
            debug(std::cout << "HIT" << std::endl);
            return true;
        }

        if (case_b1(elem) || case_b2(elem)) {
            debug(std::cout << "case B1 or B2" << std::endl);
            return false;
        }

        // CASE IV
        if (b1_.size() + t1_.size() == c_) {
            // CASE A
            debug(std::cout << "case A" << std::endl);
            if (t1_.size() < c_) {
                b1_.pop_back();
                replace(elem, p_);
            } else {
                t1_.pop_back();
            }
        } else {
            // CASE B
            debug(std::cout << "case B" << std::endl);
            int sum_size = (t1_.size() + t2_.size() + b1_.size() + b2_.size());
            if (sum_size >= c_) {
                if (sum_size == 2 * c_) {
                    b2_.pop_back();
                }

                replace(elem, p_);
            }
        }

        debug(std::cout << "add " << elem << " to t1 MRU" << std::endl);

        t1_.push_front(elem);

        return false;
    }

    int FetchElem(int elem) {
        (void)elem;
        return 0;
    }
};

#endif // ARC_CAHCE_H
