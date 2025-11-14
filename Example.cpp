#include <iostream>
#include "hashmap.h"

int main() {
    HashMap<std::string, int> map;

    map.insert("cat", 1);
    map.insert("dog", 2);

    std::cout << "cat: " << map.at("cat") << "\n";

    map.insert("cat", 99);
    std::cout << "cat after update: " << map.at("cat") << "\n";

    if (map.contains("dog"))
        std::cout << "dog found!\n";

    map.remove("dog");
    if (!map.contains("dog"))
        std::cout << "dog removed!\n";

    std::cout << "size: " << map.size() << "\n";
    return 0;
}
