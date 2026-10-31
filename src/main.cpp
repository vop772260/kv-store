#include <iostream>
#include <sstream>
#include "KeyValueStore.hpp"

int main() {
    KeyValueStore kv(3);
    std::string input;

    std::cout << "=== C++ In-Memory Key-Value Store CLI ===\n";
    std::cout << "Commands: SET <key> <val> | GET <key> | DEL <key> | SAVE <file> | LOAD <file> | EXIT\n\n";

    while (true) {
        std::cout << "kv> ";
        if (!std::getline(std::cin, input) || input == "EXIT") break;

        std::stringstream ss(input);
        std::string cmd, key, value;
        ss >> cmd;

        if (cmd == "SET") {
            ss >> key >> value;
            if (!key.empty() && !value.empty()) {
                kv.set(key, value);
                std::cout << "OK\n";
            } else {
                std::cout << "Usage: SET <key> <value>\n";
            }
        } else if (cmd == "GET") {
            ss >> key;
            if (kv.get(key, value)) {
                std::cout << "\"" << value << "\"\n";
            } else {
                std::cout << "(nil)\n";
            }
        } else if (cmd == "DEL") {
            ss >> key;
            if (kv.del(key)) std::cout << "OK\n";
            else std::cout << "(nil)\n";
        } else if (cmd == "SAVE") {
            ss >> key;
            if (kv.saveToFile(key)) std::cout << "Saved successfully.\n";
            else std::cout << "Error saving file.\n";
        } else if (cmd == "LOAD") {
            ss >> key;
            if (kv.loadFromFile(key)) std::cout << "Loaded successfully.\n";
            else std::cout << "Error loading file.\n";
        } else if (!cmd.empty()) {
            std::cout << "Unknown command.\n";
        }
    }
    return 0;
}