#include <iostream>
#include <vector>
#include <ideal_cache.hpp>

#ifdef DEBUG
#define debug(x) do { x; } while(0) 
#else
#define debug(x) do {} while(0) 
#endif // DEBUG

int main() {
    int cache_size = 0;
    int elem_num = 0;

    debug(std::cout << "Enter cache size:" << std::endl);
    std::cin >> cache_size;
    debug(std::cout << "Enter element number:" << std::endl);
    std::cin >> elem_num;

    if (cache_size <= 0) {
        std::cout << "ERROR: cache size is invalid: " << cache_size << std::endl;
        return -1;
    }

    if (elem_num <= 0) {
        std::cout << "ERROR: number of elements is invalid: " << elem_num << std::endl;
        return -1;
    }

    std::vector<int> elements(elem_num);

    int elem = 0;
    for (int i = 0; i < elem_num; i++) {
        std::cin >> elem;
        elements[i] = elem;
    }

    for (int i = 0; i < elem_num; i++) {
        std::cout << elements[i] << ' ';
    }

    std::cout << std::endl;

    IdealCache ideal(cache_size, elements);

    int hits = 0;

    for (int i = 0; i < elem_num; i++) {
        bool miss = ideal.AddElem(elements[i]);
        if (!miss) {
            hits++;
        }
    }

    debug(std::cout << "hits = ");

    std::cout << hits << std::endl;

    return 0;
}
