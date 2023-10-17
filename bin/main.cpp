
#include <lib/number.h>
#include <iostream>

int main() {
    int2023_t value1 = from_int(-32768);
    int2023_t value2 = from_string("-32768");

    std::cout << value1 << '\n' << value2 << '\n' << (value1 == value2);
}
