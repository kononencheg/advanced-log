#include <iostream>
#include <map>

int main() {
    std::cout << "Hello, World!" << std::endl;

    std::map<char, uint> my_map;
    uint d = 0;

    while (d < 10) {
        my_map.insert({ 'g', d++ });
    }

    return 0;
}