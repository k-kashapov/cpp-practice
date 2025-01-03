#ifndef CACHE_H
#define CACHE_H

#include <vector>

using slow_get_page_t = int (*)(int);

class Cache_I {
   public:
    // Returns true if cache hit occured
    virtual bool LookupUpdate(int elem) = 0;
    virtual int FetchElem(int key) = 0;
    virtual ~Cache_I() {};

   protected:
    slow_get_page_t get_page_;

    Cache_I(slow_get_page_t get_page) : get_page_(get_page) {}
};

#endif  // CACHE_H
