# kv-store
# C++ In-Memory Key-Value Store with LRU Eviction

A fast, lightweight, in-memory key-value storage engine implemented in modern **C++17**, featuring an **LRU (Least Recently Used)** cache eviction mechanism and basic file persistence.


 **$O(1)$ Operations:** Fast `SET`, `GET`, and `DEL` time complexity using `std::unordered_map` combined with a doubly-linked list (`std::list`).
 **LRU Eviction Policy:** Automatically removes the least recently used keys when the memory limit is reached.
 **Persistence:** Supports saving cache data to disk (`SAVE`) and restoring state (`LOAD`).
 **Interactive CLI:** Simple command-line interface for testing operations.


### Prerequisites
 C++17 compatible compiler (GCC/Clang/MSVC)
 CMake 3.12+

### Instructions
```bash
# Create build directory
mkdir build && cd build

# Configure & Build
cmake ..
cmake --build .

# Run CLI
./kvstore
