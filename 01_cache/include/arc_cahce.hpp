#ifndef ARC_CAHCE_H
#define ARC_CAHCE_H

#include <vector>

#ifdef DEBUG
#define debug(x) do { x; } while(0) 
#else
#define debug(x) do {} while(0) 
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

class ARCCache : Cache_I {
private:
    std::vector<int> data_;

public:
    ARCCache(int length) : data_(length, -1) {
        
    }

    bool AddElem(int elem) {

        return true;
    }

    int FetchElem(int elem) {
        (void) elem;
        return 0;
    }
};


#endif // ARC_CAHCE_H
