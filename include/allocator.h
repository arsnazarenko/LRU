#ifndef ALLOCATOR_H
#define ALLOCATOR_H
#include "pool.h"

template <class T>
class AllocatorWithPool {

public:
    AllocatorWithPool(const std::size_t count)
    : m_pool(sizeof(T), count) {}

    template<class... Args>
    T * create(Args&&... args) {
        return new (m_pool.allocate()) T(std::forward<Args>(args)...);
    }
    void destroy(const T * ptr) {
        ptr->~T();
        m_pool.deallocate(ptr);
    }

private:
    Pool m_pool;
};

#endif
