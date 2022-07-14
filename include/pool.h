#ifndef POOL_H
#define POOL_H

#include <vector>

class Pool {
public:
    Pool(const std::size_t obj_size, const std::size_t obj_count)
    : m_obj_size(obj_size)
    , m_storage(obj_size * obj_count)
    , m_used_map(obj_count)
    {}

    void* allocate();

    void deallocate(const void *);


private:
    static constexpr std::size_t npos = static_cast<std::size_t>(-1);

    std::size_t find_empty_place() const;

    const std::size_t m_obj_size;
    std::vector<std::byte> m_storage;
    std::vector<bool> m_used_map;
};

#endif
