#include <iostream>
#include <vector>
#include <ideal_cache.hpp>
#include <arc_cache.hpp>

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

    for (int i = 0; i < elem_num; i++) {
        std::cout << elements[i] << ' ';
    }

    std::cout << std::endl;

    IdealCache ideal(cache_size, elements);

    int hits = 0;

    for (int i = 0; i < elem_num; i++) {
        hits += ideal.AddElem(elements[i]);
    }

    debug(std::cout << "ideal hits = ");
    std::cout << hits << std::endl;
    debug(std::cout << std::endl);

    ARCCache arc(cache_size);

    hits = 0;
    for (int i = 0; i < elem_num; i++) {
        hits += arc.AddElem(elements[i]);
    }

    debug(std::cout << "arc hits = ");
    std::cout << hits << std::endl;

    return 0;
}
