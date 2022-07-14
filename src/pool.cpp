#include "pool.h"
#include "cassert"

void* Pool::allocate() {
    const auto pos = find_empty_place();
    if (pos != npos) {
        m_used_map[pos] = true;
        return &m_storage[pos * m_obj_size];
    }
    throw std::bad_alloc{};
}

void Pool::deallocate(const void * ptr) {
    auto b_ptr = static_cast<const std::byte *>(ptr);
    const std::byte * begin = &m_storage[0];
    const std::size_t offset = (b_ptr - begin) / m_obj_size;
    assert(((b_ptr - begin) % m_obj_size) == 0);
    if (offset < m_used_map.size()) {
        m_used_map[offset] = false;
    }
}

std::size_t Pool::find_empty_place() const {
    for (std::size_t i = 0; i < m_used_map.size(); ++i) {
        if (!m_used_map[i]) {
            return i;
        }
    }
    return npos;
}