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

    bool AddElem(int elem) override {
        future_idx_++;

        debug(std::cout << "ideal cache process elem " << elem << std::endl);

        auto found = std::find(data_.begin(), data_.end(), elem);
        if (found != data_.end()) {
            debug(std::cout << "HIT elem " << elem << std::endl);
            return true;
        }

        debug(std::cout << "future idx = " << future_idx_ << std::endl);

        if (predictions_[elem].empty() || (predictions_[elem].back() < future_idx_)) {
            // Do not cache as this element will not be encountered anymore
            debug(
                std::cout << "will not encounter " << elem << " anymore, do not cache" << std::endl;
            );
            return false;
        }

        debug(
            std::cout << "predictions[" << elem << "] = ";
            print_queue(predictions_[elem]);
        );

        if (data_.size() < len_) {
            data_.push_back(elem);
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

    int FetchElem(int elem) override {
        (void)elem;
        return 0;
    }
};

#endif // IDEAL_CACHE_H
