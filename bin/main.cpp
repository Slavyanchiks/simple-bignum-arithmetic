
#include <lib/number.h>
#include <iostream>


#include <ctime>
#include <bitset>

int main() {
    std::clock_t start;
    double duration;

    int32_t y = -1;
//    std::cout << std::bitset<32>(y) << " " << std::bitset<32>(y << 1) << '\n';

    int2023_t value1 = from_string("565465");
    int2023_t value2 = from_string("19595876546445465");

    std::cout << value2 << '\n' << value1 << '\n';

    start = std::clock();
    for (int i = 0; i < 100; ++i) {
        value1 = value2 * value1;
    }
    duration = (std::clock() - start) / (double) CLOCKS_PER_SEC;

    std::cout << duration << '\n';
//    std::cout << value1 << '\n' << value2 << '\n';
}
