#ifndef IDEAL_CACHE_H
#define IDEAL_CACHE_H

#include <iostream>
#include <map>
#include <queue>
#include <vector>
#include <algorithm>
#include "debug.hpp"
#include "cache.hpp"

class IdealCache : Cache_I {
  private:
    size_t len_;
    std::vector<int> data_;

    std::map<int, std::queue<size_t>> predictions_;
    size_t future_idx_;
    std::vector<int> future_;

  public:
    IdealCache(size_t length, std::vector<int> future)
    : len_(length), data_(), predictions_(), future_idx_(0), future_(future) {
        for (size_t i = 0; i < future_.size(); i++) {
            predictions_[future_[i]].push(i);
        }

        debug(
            std::cout << "initialized map with:\n";
            for (auto pred : predictions_) {
                int val = pred.first;
                std::cout << val << " predictions = ";
                print_queue(pred.second);
            } std::cout << std::endl;
        );
    }

    bool AddElem(int elem) override;

    int FetchElem(int elem) override {
        (void)elem;
        return 0;
    }
};

#endif // IDEAL_CACHE_H
