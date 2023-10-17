
#include <lib/number.h>
#include <iostream>
#include <ctime>

int main() {
    std::clock_t start;
    double duration;

    int2023_t value1 = from_string("443434543953859345389534859345835");
    int2023_t value2 = from_string("-443434543953859345389534859345836");

    start = std::clock();
        std::cout << value1 + value2;
    duration = (std::clock() - start) / (double) CLOCKS_PER_SEC;

    std::cout << duration << '\n';
    std::cout << value1 << '\n' << value2 << '\n';
}
