#include <ideal_cache.hpp>

bool IdealCache::LookupUpdate(int elem) {
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
        debug(std::cout << "will not encounter " << elem << " anymore, do not cache" << std::endl;);
        return false;
    }

    debug(std::cout << "predictions[" << elem << "] = "; print_queue(predictions_[elem]););

    if (data_.size() < len_) {
        data_.push_back(elem);
        return false;
    }

    size_t to_evict = 0;
    size_t max_wait = 0;

    for (size_t idx = 0; idx < data_.size(); idx++) {
        std::queue<size_t>& positions = predictions_[data_[idx]];

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

    debug(std::cout << "evicted element " << to_evict << " with value " << data_[to_evict]
                    << std::endl);

    data_[to_evict] = elem;
    get_page_(elem);

    debug(std::cout << "cache = "; print_vec(data_));

    return false;
}
