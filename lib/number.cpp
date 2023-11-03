#include "number.h"

const int2023_t kShortSizeLenMask = from_int(65535);
const int2023_t kZeroValue = from_int(0);

int2023_t from_int(int32_t number) {
    int2023_t val;

    if (number < 0) {
        val = ~val;
    }

    for (int i = 0; i < int2023_t::kInt32Size; ++i) {
        val.digit[int2023_t::kInt2023Size - i - 1] = static_cast<uint8_t>(number % kOutputNumBase);
        number = number >> int2023_t::kUint8Size;
    }

    return val;
}

void divide_long_by2 (char* buff_copy, int& str_len) {
    char next_buff[str_len];
    int iter_next_buff = 0;
    int next_num = 0;

    int iter_buff_copy = 0;
    while (iter_buff_copy < str_len) {
        int division_value = (static_cast<int>(buff_copy[iter_buff_copy]) - kASCIIFirstNumSymbolCode) * 5;

        if (division_value == 5 && next_num == 0 && iter_buff_copy == 0) {
            next_num = division_value;
        } else {
            next_buff[iter_next_buff] = static_cast<char>(kASCIIFirstNumSymbolCode + division_value / kInputNumBase + next_num);
            next_num = division_value % kInputNumBase;
            ++iter_next_buff;
        }

        ++iter_buff_copy;
    }

    for (int i = 0; i < iter_next_buff; ++i) {
        buff_copy[i] = next_buff[i];
    }

    str_len = iter_next_buff;
}

int2023_t from_string(const char* buff) {
    int2023_t result;
    auto str_len = static_cast<int32_t>(strlen(buff));
    bool is_positive = true;
    bool eol = false;

    if (buff[0] == '0') {
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

    int16_t iter_to8 = 0;
    int16_t iter_digit = int2023_t::kInt2023Size - 1;
    int digit_value = 0;
    int pow_num = 1;

    while (!eol) {
        if (iter_to8 == int2023_t::kUint8Size) {
            result.digit[iter_digit] = digit_value;

            --iter_digit;
            iter_to8 = 0;
            digit_value = 0;
            pow_num = 1;

            if (iter_digit < 0) {
                iter_digit = int2023_t::kInt2023Size - 1;
            }
        }

        digit_value += ((static_cast<int>(buff_copy[str_len - 1]) - kASCIIFirstNumSymbolCode) % kBinaryNumBase) * pow_num;
        pow_num *= kBinaryNumBase;
        ++iter_to8;

        if (buff_copy[0] == '1' && str_len == 1) {
            eol = true;
        } else {
            divide_long_by2(buff_copy, str_len);
        }
    }
    result.digit[iter_digit] = digit_value;

    return is_positive ? result : -result;
}

int2023_t operator+(const int2023_t& lhs, const int2023_t& rhs) {
    int2023_t result;
    int16_t digit_transition = 0;

    for (int i = int2023_t::kInt2023Size - 1; i > -1; --i) {
        result.digit[i] = (lhs.digit[i] + rhs.digit[i] + digit_transition) % kOutputNumBase;
        if ((lhs.digit[i] + rhs.digit[i] + digit_transition) > kOutputNumBase - 1) {
            digit_transition = 1;
        } else {
            digit_transition = 0;
        }
    }

    return result;
}

int2023_t operator-(const int2023_t& lhs, const int2023_t& rhs) {
    return lhs + (-rhs);
}

int2023_t shift_digit_left(const int2023_t& value, short shift) {
    int2023_t result;

    for (short i = shift; i < int2023_t::kInt2023Size; ++i) {
        result.digit[i - shift] = value.digit[i];
    }

    return result;
}

int2023_t shift_digit_right(const int2023_t& value, short shift) {
    int2023_t result;

    for (short i = int2023_t::kInt2023Size - 1; i > shift - 1; --i) {
        result.digit[i] = value.digit[i - shift];
    }

    return result;
}

int2023_t karatsuba_multiplying(const int2023_t& left, const int2023_t& right) {

    if (right == kZeroValue || left == kZeroValue) {
        return from_int(0);
    }

    if ((left | kShortSizeLenMask) == kShortSizeLenMask && (right | kShortSizeLenMask) == kShortSizeLenMask) {
        uint32_t num = (left.digit[int2023_t::kInt2023Size - 2] << 8 | left.digit[int2023_t::kInt2023Size - 1]) * (right.digit[int2023_t::kInt2023Size - 2] << 8 | right.digit[int2023_t::kInt2023Size - 1]);

        int2023_t res;
        for (int i = 0; i < int2023_t::kInt32Size; ++i) {
            res.digit[int2023_t::kInt2023Size - i - 1] = static_cast<uint8_t>(num % kOutputNumBase);
            num = num >> int2023_t::kUint8Size;
        }

        return res;
    }

    // (a*x + c)*(b*x + d) = ab*x^2 + (ad + bc)*x + cd   <- Karatsuba multiplying method
    int2023_t ab = karatsuba_multiplying(shift_digit_right(left, 2), shift_digit_right(right, 2));
    int2023_t ad_bc = karatsuba_multiplying(shift_digit_right(left, 2), right & kShortSizeLenMask) + karatsuba_multiplying(shift_digit_right(right, 2), left & kShortSizeLenMask);
    int2023_t cd = karatsuba_multiplying(left & kShortSizeLenMask, right & kShortSizeLenMask);

    return shift_digit_left(ab, 4) + shift_digit_left(ad_bc, 2) + cd;
}

int2023_t operator*(const int2023_t& lhs, const int2023_t& rhs) {
    int2023_t result;
//    int2023_t lhs_copy = is_negative(lhs) ? -lhs : lhs;
//    int2023_t rhs_copy = is_negative(rhs) ? -rhs : rhs;

    if (is_negative(lhs) && is_negative(rhs)) {
        result = karatsuba_multiplying(-lhs, -rhs);
    } else if (is_negative(lhs)) {
        result = karatsuba_multiplying(-lhs, rhs);
    } else if (is_negative(rhs)) {
        result = karatsuba_multiplying(lhs, -rhs);
    } else {
        result = karatsuba_multiplying(lhs, rhs);
    }

    if (is_negative(lhs) ^ is_negative(rhs)) {
        return -result;
    }

    return result;
}

int2023_t& shift_bit_through_digit_right(int2023_t& value) {
    for (int i = int2023_t::kInt2023Size - 1; i > 0; --i) {
        value.digit[i] = value.digit[i] >> 1;
        uint8_t last_bit = value.digit[i - 1] << 7;
        value.digit[i] = value.digit[i] | last_bit;
    }
    value.digit[0] = value.digit[0] >> 1;

    return value;
}

int2023_t division(const int2023_t& left, const int2023_t& right, const int2023_t& numerator, const int2023_t& denominator) {
    int2023_t middle = left + right;
    shift_bit_through_digit_right(middle);
    int2023_t multiplication = middle * denominator;

    int2023_t main_diff = multiplication - numerator;
    int2023_t supplement_diff = (multiplication + denominator) - numerator;

    if (is_negative(main_diff) && !is_negative(supplement_diff)) {
        return middle;
    }

    if (is_negative(main_diff)) {
        return division(middle, right, numerator, denominator);
    } else {
        return division(left, middle, numerator, denominator);
    }
}

int2023_t operator/(const int2023_t& lhs, const int2023_t& rhs) {
    int2023_t result;
    int2023_t numerator = is_negative(lhs) ? -lhs : lhs;
    int2023_t denominator = is_negative(rhs) ? -rhs : rhs;

    int2023_t delta = numerator - denominator;
    if (is_negative(delta) || numerator == kZeroValue) {
        return from_int(0);
    }

    if (denominator == kZeroValue) {
        std::cerr << "ZeroDivisionError: division by zero";
        return from_int(0);
    }
    if (numerator == denominator) {
        return from_int(1);
    }

    if (denominator == from_int(1)) {
        result = numerator;
        if (is_negative(lhs) ^ is_negative(rhs)) {
            return -result;
        }
        return result;
    }

    short numer_digit_count = 0;
    short denom_digit_count = 0;

    while (numerator.digit[numer_digit_count] == 0) {
        ++numer_digit_count;
    }
    while (denominator.digit[denom_digit_count] == 0) {
        ++denom_digit_count;
    }
    int2023_t right;
    for (short i = 0; i < denom_digit_count - numer_digit_count + 2; ++i) {
        right.digit[int2023_t::kInt2023Size - 1 - i] = 255;
    }

    result = division(kZeroValue, right, numerator, denominator);

    if (is_negative(lhs) ^ is_negative(rhs)) {
        return -result;
    }

    return result;
}

int2023_t operator~(const int2023_t& rhs) {
    int2023_t value;

    for (int i = 0; i < int2023_t::kInt2023Size; ++i) {
        value.digit[i] = ~(rhs.digit[i]);
    }

    return value;
}

int2023_t operator-(const int2023_t& rhs) {
    return ~rhs + from_int(1);
}

int2023_t operator&(const int2023_t& lhs, const int2023_t& rhs) {
    int2023_t result;

    for (int i = 0; i < int2023_t::kInt2023Size; ++i) {
        result.digit[i] = lhs.digit[i] & rhs.digit[i];
    }

    return result;
}

int2023_t operator|(const int2023_t& lhs, const int2023_t& rhs) {
    int2023_t result;

    for (int i = 0; i < int2023_t::kInt2023Size; ++i) {
        result.digit[i] = lhs.digit[i] | rhs.digit[i];
    }

    return result;
}

bool operator==(const int2023_t& lhs, const int2023_t& rhs) {
    for (int i = 0; i < int2023_t::kInt2023Size; ++i) {
        if (rhs.digit[i] - lhs.digit[i]) {
            return false;
        }
    }
    return true;
}

bool operator!=(const int2023_t& lhs, const int2023_t& rhs) {
    return !(lhs == rhs);
}

bool is_negative(const int2023_t& value) {
    if (value.digit[0] >= kMinValToNegative) {
        return true;
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
