#ifndef KEY_VALUE_STORE_HPP
#define KEY_VALUE_STORE_HPP

#include <string>
#include <unordered_map>
#include <list>
#include <utility>

class KeyValueStore {
private:
    size_t capacity;
    std::list<std::string> lru_keys;
    using ListIterator = std::list<std::string>::iterator;
    std::unordered_map<std::string, std::pair<std::string, ListIterator>> cache;

public:
    explicit KeyValueStore(size_t cap);

    void set(const std::string& key, const std::string& value);
    bool get(const std::string& key, std::string& out_value);
    bool del(const std::string& key);

    bool saveToFile(const std::string& filename) const;
    bool loadFromFile(const std::string& filename);
};

#endif
