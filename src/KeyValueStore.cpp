#include "KeyValueStore.hpp"
#include <fstream>
#include <iostream>

KeyValueStore::KeyValueStore(size_t cap) : capacity(cap) {}

void KeyValueStore::set(const std::string& key, const std::string& value) {
    auto it = cache.find(key);

    if (it != cache.end()) {
        it->second.first = value;
        lru_keys.erase(it->second.second);
        lru_keys.push_front(key);
        it->second.second = lru_keys.begin();
        return;
    }

    if (cache.size() >= capacity) {
        std::string oldest_key = lru_keys.back();
        lru_keys.pop_back();
        cache.erase(oldest_key);
        std::cout << "[Cache Full] Auto-evicted LRU key: " << oldest_key << "\n";
    }

    lru_keys.push_front(key);
    cache[key] = {value, lru_keys.begin()};
}

bool KeyValueStore::get(const std::string& key, std::string& out_value) {
    auto it = cache.find(key);
    if (it == cache.end()) {
        return false;
    }

    lru_keys.erase(it->second.second);
    lru_keys.push_front(key);
    it->second.second = lru_keys.begin();

    out_value = it->second.first;
    return true;
}

bool KeyValueStore::del(const std::string& key) {
    auto it = cache.find(key);
    if (it == cache.end()) return false;

    lru_keys.erase(it->second.second);
    cache.erase(it);
    return true;
}

bool KeyValueStore::saveToFile(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) return false;

    for (const auto& [key, pair_val] : cache) {
        file << key << "=" << pair_val.first << "\n";
    }
    return true;
}

bool KeyValueStore::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) return false;

    std::string line;
    while (std::getline(file, line)) {
        size_t pos = line.find('=');
        if (pos != std::string::npos) {
            std::string k = line.substr(0, pos);
            std::string v = line.substr(pos + 1);
            set(k, v);
        }
    }
    return true;
}