#include <algorithm>
#include <arc_cache.hpp>

void ARCCache::replace(size_t p, bool in_b2) {
    if ((!cached_ref_once.empty()) &&
        ((cached_ref_once.size() > p) || (in_b2 && (cached_ref_once.size() == p)))) {
        ghost_ref_once.splice(ghost_ref_once.begin(), cached_ref_once,
                              std::prev(cached_ref_once.end()));
        elem_to_iter[ghost_ref_once.front()] = list_info{B1, ghost_ref_once.begin()};
    } else {
        ghost_ref_mult.splice(ghost_ref_mult.begin(), cached_ref_mult,
                              std::prev(cached_ref_mult.end()));
        elem_to_iter[ghost_ref_mult.front()] = list_info{B2, ghost_ref_mult.begin()};
    }
}

bool ARCCache::case_hit(int elem, list_info& info) {
    if (info.list_num == T1) {
        // CACHE HIT
        // => move element to MRU (begin) in t2
        cached_ref_mult.splice(cached_ref_mult.begin(), cached_ref_once, info.iter);
        elem_to_iter[elem].list_num = T2;
        return true;
    } else if (info.list_num == T2) {
        // CACHE HIT
        // => move element to MRU (begin) in t2
        cached_ref_mult.splice(cached_ref_mult.begin(), cached_ref_mult, info.iter);
        return true;
    }

    return false;
}

bool ARCCache::case_b1(list_info& info) {
    if (info.list_num == B1) {
        // CASE 2 from paper
        size_t delta = ghost_ref_once.size() >= ghost_ref_mult.size()
                           ? 1
                           : ghost_ref_mult.size() / ghost_ref_once.size();

        // Case 2 in paper says p = min(p + delta, c)
        adapt_param = std::min(adapt_param + delta, capacity);

        replace(adapt_param, false);

        cached_ref_mult.splice(cached_ref_mult.begin(), ghost_ref_once, info.iter);
        info.list_num = T2;

        get_page_(*info.iter);
        return true;
    }

    return false;
}

bool ARCCache::case_b2(list_info& info) {
    if (info.list_num == B1) {
        // CASE 3 from paper
        size_t delta = ghost_ref_mult.size() >= ghost_ref_once.size()
                           ? 1
                           : ghost_ref_once.size() / ghost_ref_mult.size();

        // Case 3 in paper says p = max(p - delta, 0)
        adapt_param = std::clamp(adapt_param - delta, 0lu, adapt_param);

        replace(adapt_param, true);

        cached_ref_mult.splice(cached_ref_mult.begin(), ghost_ref_mult, info.iter);
        info.list_num = T2;

        get_page_(*info.iter);
        return true;
    }

    return false;
}

void ARCCache::case_l1_full(int elem) {
    debug(std::cout << "case A: b1 size = " << b1_.size() << ", t1 size = " << t1_.size()
                    << ", c_ = " << c_ << std::endl);
    if (cached_ref_once.size() < capacity) {
        elem_to_iter.erase(ghost_ref_once.back());
        ghost_ref_once.pop_back();
        replace(elem, adapt_param);
    } else {
        debug(std::cout << "t1 back = " << t1_.back() << std::endl);
        elem_to_iter.erase(cached_ref_once.back());
        cached_ref_once.pop_back();
    }
}

void ARCCache::case_l1_less(int elem) {
    debug(std::cout << "case B" << std::endl);
    size_t sum_size = (cached_ref_once.size() + cached_ref_mult.size() + ghost_ref_once.size() +
                       ghost_ref_mult.size());
    if (sum_size >= capacity) {
        if (sum_size == 2 * capacity) {
            elem_to_iter.erase(ghost_ref_mult.back());
            ghost_ref_mult.pop_back();
        }

        replace(elem, adapt_param);
    }
}

bool ARCCache::case_miss(int elem) {
    if (ghost_ref_once.size() + cached_ref_once.size() == capacity) {
        // CASE A
        case_l1_full(elem);
    } else {
        // CASE B
        case_l1_less(elem);
    }

    debug(std::cout << "add " << elem << " to t1 MRU" << std::endl);

    cached_ref_once.push_front(elem);
    elem_to_iter[elem] = list_info{T1, cached_ref_once.begin()};

    get_page_(elem);
    return false;
}

bool ARCCache::LookupUpdate(int elem) {
    auto search = elem_to_iter.find(elem);
    auto& info = search->second;

    if (search != elem_to_iter.end()) {
        // CASE I
        if (case_hit(elem, info)) {
            debug(std::cout << "ARC HIT elem = " << elem << std::endl);
            return true;
        }

        // CASE II
        if (case_b1(info)) {
            debug(std::cout << "case B1" << std::endl);
            return false;
        }

        // CASE III
        if (case_b2(info)) {
            debug(std::cout << "case B2" << std::endl);
            return false;
        }
    }

    // CASE IV
    return case_miss(elem);
}
