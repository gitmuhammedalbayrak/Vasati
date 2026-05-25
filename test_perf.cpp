#include "include/include-class/Zaman.hpp"
#include <chrono>
#include <iostream>

int main() {
    std::cout.setstate(std::ios_base::failbit); // Suppress output
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 100000; ++i) {
        zaman z;
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::cout.clear(); // Restore output
    std::chrono::duration<double> diff = end - start;
    std::cout << "Time: " << diff.count() << " s\n";
    return 0;
}
