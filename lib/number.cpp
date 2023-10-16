#include "number.h"


int2023_t from_int(int32_t number) {
    int2023_t val;

    if (number < 0) {
        val = ~val;
    }

    for (int i = 0; i < kInt32Size; ++i) {
        val.digit[kInt2023Size - i - 1] = static_cast<uint8_t>(number % 256);
        number = number >> 8;
    }

    return val;
}

int32_t to_int(const int2023_t& val) {
    int32_t result = 0;
    int pow_num = 1;
    for (int i = 0; i < kInt32Size; ++i) {
        result += val.digit[kInt2023Size - 1 - i] * (pow_num);
        pow_num *= 256;
    }

    return result;
}

int2023_t from_string(const char* buff) {
    return int2023_t();
}

int2023_t operator+(const int2023_t& lhs, const int2023_t& rhs) {
    int2023_t result;
    short digit_transition = 0;

    for (int i = kInt2023Size - 1; i > -1; --i) {
        result.digit[i] = (lhs.digit[i] + rhs.digit[i] + digit_transition) % 256;
        if (lhs.digit[i] + rhs.digit[i] > 255) {
            digit_transition = 1;
        }
    }

    return result;
}

int2023_t operator-(const int2023_t& lhs, const int2023_t& rhs) {
    int2023_t right_operand = ~rhs + from_int(1);

    return lhs + right_operand;
}

int2023_t operator*(const int2023_t& lhs, const int2023_t& rhs) {
    return int2023_t();
}

int2023_t operator/(const int2023_t& lhs, const int2023_t& rhs) {
    return int2023_t();
}

int2023_t operator~(const int2023_t& rhs) {
    int2023_t value;

    for (int i = 0; i < kInt2023Size; ++i) {
        value.digit[i] = ~(rhs.digit[i]);
    }

    return value;
}

bool operator==(const int2023_t& lhs, const int2023_t& rhs) {
    for (int i = 0; i < kInt2023Size; ++i) {
        if (rhs.digit[i] - lhs.digit[i]) {
            return false;
        }
    }
    return true;
}

bool operator!=(const int2023_t& lhs, const int2023_t& rhs) {
    for (int i = 0; i < kInt2023Size; ++i) {
        if (rhs.digit[i] - lhs.digit[i]) {
            return true;
        }
    }
    return false;
}

std::ostream& operator<<(std::ostream& stream, const int2023_t& value) {
    stream << "256 x ";

    for (uint8_t i : value.digit) {
        stream << '(' << static_cast<int>(i) << ')';
    }

    return stream;
}
