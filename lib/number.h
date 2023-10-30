#pragma once
#include <cinttypes>
#include <iostream>
#include <cstring>

const uint8_t kASCIIMinusCode = 45;
const uint8_t kASCIIFirstNumSymbolCode = 48;
const int8_t kInputNumBase = 10;
const int8_t kBinaryNumBase = 2;
const int32_t kOutputNumBase = 256;
const int32_t kMinValToNegative = 128;

struct int2023_t {
    static const size_t kInt2023Size = 253;
    static const size_t kInt32Size = 4;
    static const size_t kUint8Size = 8;

    uint8_t digit[kInt2023Size]{};

    int2023_t() = default;
    int2023_t(const int2023_t& value) = default;
};

static_assert(sizeof(int2023_t) <= 253, "Size of int2023_t must be no higher than 253 bytes");

int2023_t from_int(int32_t i);

int2023_t from_string(const char* buff);

int2023_t operator+(const int2023_t& lhs, const int2023_t& rhs);

int2023_t operator-(const int2023_t& lhs, const int2023_t& rhs);

int2023_t shift_digit_left(const int2023_t& value, short shift);

int2023_t shift_digit_right(const int2023_t& value, short shift);

int2023_t& shift_bit_through_digit_right(int2023_t& value);

int2023_t operator*(const int2023_t& lhs, const int2023_t& rhs);

int2023_t division(const int2023_t& left, const int2023_t& right,const int2023_t& numerator, const int2023_t& denominator);

int2023_t operator/(const int2023_t& lhs, const int2023_t& rhs);

int2023_t operator~(const int2023_t& lhs);

int2023_t operator-(const int2023_t& rhs);

int2023_t operator&(const int2023_t& lhs, const int2023_t& rhs);

int2023_t operator|(const int2023_t& lhs, const int2023_t& rhs);

bool operator==(const int2023_t& lhs, const int2023_t& rhs);

bool operator!=(const int2023_t& lhs, const int2023_t& rhs);

bool is_negative(const int2023_t& value);

std::ostream& operator<<(std::ostream& stream, const int2023_t& value);
