#include <ctime>
#include <lib/number.h>
#include <iostream>

int main() {
    std::clock_t start;
    double duration;

    int2023_t value1 = from_string("255");
    int2023_t value2 = from_string("255");

    start = std::clock();
    for (int i = 0; i < 1000; ++i) {
        // put your code here
    }
    duration = (std::clock() - start) / (double) CLOCKS_PER_SEC;

    std::cout << duration << '\n';
}
