#ifndef IDEAL_CACHE_H
#define IDEAL_CACHE_H

#include "cache.hpp"
#include <iostream>
#include <map>
#include <queue>
#include <vector>

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

#ifdef DEBUG
void print_queue(std::queue<size_t> &q) {
    size_t len = q.size();
    for (size_t i = 0; i < len; i++) {
        int tmp = q.front();
        q.pop();
        std::cout << tmp << ", ";
        q.push(tmp);
    }
}

void print_vec(std::vector<int> &v) {
    std::cout << "[";
    for (size_t i = 0; i < v.size(); i++) {
        std::cout << v[i] << ", ";
    }
    std::cout << "\b\b]\n";
}

#endif // DEBUG

class IdealCache : Cache_I {
  private:
    size_t len_ = 0;
    std::vector<int> data_;

    std::map<int, std::queue<size_t>> predictions_;
    size_t future_idx_ = 0;
    std::vector<int> future_;

  public:
    IdealCache(int length, std::vector<int> future)
        : data_(length, -1), future_(future) {
        predictions_ = std::map<int, std::queue<size_t>>();
        for (size_t i = 0; i < future_.size(); i++) {
            predictions_[future_[i]].push(i);
        }

        debug(
            std::cout << "initialized map with:\n";
            for (auto pred : predictions_) {
                int val = pred.first;
                std::cout << val << " at [";

                print_queue(pred.second);

                std::cout << "\b\b]" << std::endl;
            } std::cout << std::endl;
        );
    }

    bool AddElem(int elem) {
        future_idx_++;

        for (int our : data_) {
            if (our == elem) {
                return true;
            }
        }

        if (len_ < data_.size()) {
            data_[len_++] = elem;
            return false;
        }

        size_t to_evict = 0;
        size_t max_wait = 0;

        for (size_t idx = 0; idx < data_.size(); idx++) {
            std::queue<size_t> &positions = predictions_[data_[idx]];

            // Remove all indexes that are in the past
            while (!positions.empty() && (positions.front() < future_idx_)) {
                positions.pop();
            }

            // If this element will not be encountered anymore, it has to be
            // evicted
            if (positions.empty()) {
                to_evict = idx;
                break;
            }

            // Evict the least soon used element
            if (positions.front() > max_wait) {
                max_wait = positions.front();
                to_evict = idx;
            }
        }

        debug(std::cout << "evicted element " << to_evict << " with value "
                        << data_[to_evict] << std::endl);

        data_[to_evict] = elem;

        debug(std::cout << "cache = "; print_vec(data_));

        return false;
    }

    int FetchElem(int elem) {
        (void)elem;
        return 0;
    }
};

#endif // IDEAL_CACHE_H
