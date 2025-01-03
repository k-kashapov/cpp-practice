#include <debug.hpp>
#include <ideal_cache.hpp>
#include <iostream>
#include <vector>

int slow_get_page(int key) {
    return key;
}

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

    for (int i = 0; i < elem_num; i++) {
        std::cin >> elements[i];
    }

    debug(for (int i = 0; i < elem_num; i++) { std::cout << elements[i] << ' '; }

              std::cout
              << std::endl;);

    IdealCache ideal(cache_size, slow_get_page, elements);

    int hits = 0;

    for (int elem : elements) {
        hits += ideal.LookupUpdate(elem);
    }

    debug(std::cout << "ideal hits = ");
    std::cout << hits << std::endl;

    return 0;
}
