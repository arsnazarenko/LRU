#include <iostream>
#include <string>
#include "lru.h"

namespace {

struct String {
    int key;
    std::string data;

    String(const int key_)
    : key(key_)
    , data(std::to_string(key_))
    {}

    bool operator==(const int other_key) const {
        return key == other_key;
    }

    bool operator!=(const int other_key) const {
        return key != other_key;
    }

    friend std::ostream& operator<<(std::ostream& strm, const String& s) {
        return strm << s.key << "[" << s.data << "]";
    }

};


} // anon namespace


using Cache = LRU<int, String>;


int main() {

    Cache cache(10);

    cache.get(1);
    cache.get(2);
    cache.get(1);
    cache.debug_dump(std::cout);

    for (int i = 0; i < 30; ++i) {
        cache.get(i).data += '@';
    }

    cache.get(22);
    cache.get(27);
    cache.debug_dump(std::cout);

    for (int i = 29; i > 19; --i) {
        cache.get(i).data += '!';
    }

    cache.debug_dump(std::cout);
    for (int i = 10; i < 20; ++i) {
        cache.get(i);
    }

    cache.debug_dump(std::cout);


    return 0;
}