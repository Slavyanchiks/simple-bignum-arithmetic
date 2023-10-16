
#include <lib/number.h>
#include <iostream>

int main() {
    int2023_t value1;
    int2023_t value2;
    int32_t val = -20;
    int32_t val2 = -20;
    value1 = from_int(val);
    value2 = from_int(val2);
    std::cout << to_int(value1 - value2) << " " << (value1 == value2);
    return 0;
}
