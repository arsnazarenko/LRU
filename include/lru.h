#ifndef LRU_H
#define LRU_H

#include <list>
#include <type_traits>
#include <ostream>
#include <algorithm>
#include "allocator.h"


template<class Key, class T>
class LRU {
    static_assert(std::is_constructible_v<T, const Key&>, "T has to be constructible from Key ");
    using Alloc = AllocatorWithPool<T>;
public:
    LRU(const std::size_t cache_size)
    : m_max_size(cache_size), m_alloc(cache_size)
    {}

    std::size_t size() const {
        return m_queue.size();
    }

    bool empty() const {
        return m_queue.empty();
    }

    T& get(const Key& key) {
        auto it =  std::find_if(m_queue.begin(), m_queue.end(), [&key](const T * ptr) {
            return *ptr == key;
        });
        if (it != m_queue.end()) {
            m_queue.splice(m_queue.begin(), m_queue, it);
        } else {
            if (m_max_size == m_queue.size()) {
                m_alloc.destroy(m_queue.back());
                m_queue.pop_back();
            }
            m_queue.push_front(m_alloc.create(key));
        }
        return *m_queue.front();
    }

    void debug_dump(std::ostream & strm) const {
        bool first = true;
        for (const auto ptr: m_queue) {
            if (!first) {
                strm << " ";
            } else {
                first = false;
            }
            strm << *ptr;
        }
        strm << "\n";
    }



private:
    const std::size_t m_max_size;
    Alloc m_alloc;
    std::list<T *> m_queue;
};

#endif
