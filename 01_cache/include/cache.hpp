#ifndef CACHE_H
#define CACHE_H

#include <vector>

class Cache_I {
public:
    // Returns true if cache miss occured
    virtual bool AddElem(int elem) = 0;
    virtual int FetchElem(int key) = 0;
};

#endif // CACHE_H
