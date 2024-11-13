#include <arc_cache.hpp>

void ARCCache::replace(size_t p, bool in_b2) {
    if ((!t1_.empty()) && ((t1_.size() > p) || (in_b2 && (t1_.size() == p)))) {
        b1_.splice(b1_.begin(), t1_, std::prev(t1_.end()));
        elem_to_iter[b1_.front()] = list_info{ B1, b1_.begin() };
    } else {
        b2_.splice(b2_.begin(), t2_, std::prev(t2_.end()));
        elem_to_iter[b2_.front()] = list_info{ B2, b2_.begin() };
    }
}

bool ARCCache::case_hit(int elem, list_info& info) {
    if (info.list_num == T1) {
        // CACHE HIT
        // => move element to MRU (begin) in t2
        t2_.splice(t2_.begin(), t1_, info.iter);
        elem_to_iter[elem].list_num = T2;
        return true;
    } else if (info.list_num == T2) {
        // CACHE HIT
        // => move element to MRU (begin) in t2
        t2_.splice(t2_.begin(), t2_, info.iter);
        return true;
    }

    return false;
}

bool ARCCache::case_b1(list_info& info) {
    if (info.list_num == B1) {
        // CASE 2 from paper
        size_t delta = b1_.size() >= b2_.size() ? 1 : b2_.size() / b1_.size();
        p_ = std::min(p_ + delta, c_);

        replace(p_, false);

        t2_.splice(t2_.begin(), b1_, info.iter);
        info.list_num = T2;
        return true;
    }

    return false;
}

bool ARCCache::case_b2(list_info& info) {
    if (info.list_num == B1) {
        // CASE 3 from paper
        int delta = b2_.size() >= b1_.size() ? 1 : b1_.size() / b2_.size();
        p_ = std::max((int)p_ - delta, 0);
        
        replace(p_, true);

        t2_.splice(t2_.begin(), b2_, info.iter);
        info.list_num = T2;
        return true;
    }

    return false;
}

bool ARCCache::AddElem(int elem) {
    auto search = elem_to_iter.find(elem);

    if (search != elem_to_iter.end()) {
        auto& info = search->second;

        if (case_hit(elem, info)) {
            debug(std::cout << "ARC HIT elem = " << elem << std::endl);
            return true;
        }

        if (case_b1(info) || case_b2(info)) {
            debug(std::cout << "case B1 or B2" << std::endl);
            return false;
        }
    }

    // CASE IV
    if (b1_.size() + t1_.size() == c_) {
        // CASE A
        debug(std::cout << "case A: b1 size = " << b1_.size() 
                        << ", t1 size = " << t1_.size() 
                        << ", c_ = " << c_ << std::endl);
        if (t1_.size() < c_) {
            elem_to_iter.erase(b1_.back());
            b1_.pop_back();
            replace(elem, p_);
        } else {
            debug(std::cout << "t1 back = " << t1_.back() << std::endl);
            elem_to_iter.erase(t1_.back());
            t1_.pop_back();
        }
    } else {
        // CASE B
        debug(std::cout << "case B" << std::endl);
        size_t sum_size = (t1_.size() + t2_.size() + b1_.size() + b2_.size());
        if (sum_size >= c_) {
            if (sum_size == 2 * c_) {
                elem_to_iter.erase(b2_.back());
                b2_.pop_back();
            }

            replace(elem, p_);
        }
    }

    debug(std::cout << "add " << elem << " to t1 MRU" << std::endl);

    t1_.push_front(elem);
    elem_to_iter[elem] = list_info{T1, t1_.begin()};

    return false;
}
