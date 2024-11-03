#ifndef DEBUG_H
#define DEBUG_H

#ifdef DEBUG

#define debug(x)                                                               \
    do {                                                                       \
        x;                                                                     \
    } while (0)

inline void print_queue(std::queue<size_t> &q) {
    size_t len = q.size();
    std::cout << "[";
    for (size_t i = 0; i < len; i++) {
        int tmp = q.front();
        q.pop();
        std::cout << tmp << ", ";
        q.push(tmp);
    }
    std::cout << "\b\b]\n";
}

inline void print_vec(std::vector<int> &v) {
    std::cout << "[";
    for (int elem : v) {
        std::cout << elem << ", ";
    }
    std::cout << "\b\b]\n";
}

#else // !DEBUG

#define debug(x)                                                               \
    do {                                                                       \
    } while (0)

#define print_queue(x) debug(x)
#define print_vec(x) debug(x)

#endif // DEBUG

#endif // DEBUG_H