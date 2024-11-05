#include <iostream>
#include <vector>
#include <arc_cache.hpp>
#include <debug.hpp>

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

    debug(
    for (int i = 0; i < elem_num; i++) {
            std::cout << elements[i] << ' ';
    }
    std::cout << std::endl;);

    ARCCache arc(cache_size);

    int hits = 0;
    for (int elem : elements) {
        hits += arc.AddElem(elem);
    }

    debug(std::cout << "arc hits = ");
    std::cout << hits << std::endl;

    return 0;
}
