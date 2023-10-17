#include "number.h"


int2023_t from_int(int32_t number) {
    int2023_t val;

    if (number < 0) {
        val = ~val;
    }

    for (int i = 0; i < kInt32Size; ++i) {
        val.digit[kInt2023Size - i - 1] = static_cast<uint8_t>(number % kOutputNumBase);
        number = number >> kUint8Size;
    }

    return val;
}

int32_t to_int(const int2023_t& val) {
    int32_t result = 0;
    int pow_num = 1;
    for (int i = 0; i < kInt32Size; ++i) {
        result += val.digit[kInt2023Size - 1 - i] * (pow_num);
        pow_num *= kOutputNumBase;
    }

    return result;
}

int2023_t from_string(const char* buff) {
    int2023_t result;
    auto str_len = static_cast<int32_t>(strlen(buff));
    bool is_positive = true;
    bool eol = false;

    if (strncmp(buff, "0", 1) == 0) {
        return result;
    }

    if (buff[0] == kASCIIMinusCode) {
        --str_len;
        is_positive = false;
    }

    char buff_copy[str_len + 1];
    for (int i = 0; i < str_len; ++i) {
        buff_copy[i] = buff[is_positive ? i : i + 1];
    }
    buff_copy[str_len] = '\0';

    int iter_to8 = 0;
    int iter_digit = kInt2023Size - 1;
    int digit_value = 0;
    int pow_num = 1;
    int previous_num = 0;

    while (!eol) {
        if (iter_to8 == kUint8Size) {
            result.digit[iter_digit] = digit_value;

            --iter_digit;
            iter_to8 = 0;
            digit_value = 0;
            pow_num = 1;
        }

        digit_value += ((static_cast<int>(buff_copy[str_len - 1]) - kASCIIFirstNumSymbolCode) % kBinaryNumBase) * pow_num;
        pow_num *= kBinaryNumBase;
        ++iter_to8;

        if (strncmp(buff_copy, "1", 1) == 0 && str_len == 1) {
            eol = true;
        } else {
            char next_buff[str_len];
            int iter_next_buff = 0;

            int iter_buff_copy = 0;
            while (iter_buff_copy < str_len) {
                int division_value = (static_cast<int>(buff_copy[iter_buff_copy]) - kASCIIFirstNumSymbolCode) * 5;

                if (division_value == 5 && previous_num == 0 && iter_buff_copy == 0) {
                    previous_num = division_value;
                } else {
                    next_buff[iter_next_buff] = static_cast<char>(kASCIIFirstNumSymbolCode + division_value / kInputNumBase + previous_num);
                    previous_num = division_value % kInputNumBase;
                    ++iter_next_buff;
                }

                ++iter_buff_copy;
            }

            for (int i = 0; i < iter_next_buff; ++i) {
                buff_copy[i] = next_buff[i];
            }

            str_len = iter_next_buff;
            previous_num = 0;
        }
    }
    result.digit[iter_digit] = digit_value;

    if (!is_positive) {
        return ~(result) + from_int(1);
    }

    return result;
}

int2023_t operator+(const int2023_t& lhs, const int2023_t& rhs) {
    int2023_t result;
    short digit_transition = 0;

    for (int i = kInt2023Size - 1; i > -1; --i) {
        result.digit[i] = (lhs.digit[i] + rhs.digit[i] + digit_transition) % kOutputNumBase;
        if (lhs.digit[i] + rhs.digit[i] > kOutputNumBase - 1) {
            digit_transition = 1;
        } else {
            digit_transition = 0;
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
