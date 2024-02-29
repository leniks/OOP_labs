#include "Four.hpp"

bool isFour(const char &c) {
    return ('0' <= c && c <= '3');
}

Four::Four() : size(0), number{nullptr} {
}

size_t Four::getSize() const {
    return size;
}

unsigned char *Four::getNumber() const {
    return number;
}

Four::Four(const size_t &n, unsigned char t) {
    number = new unsigned char[n];
    for (size_t i = 0; i < n; i++)
        number[i] = t;
    size = n;
}

Four::Four(const std::initializer_list<unsigned char> &t) {
    number = new unsigned char[t.size()];
    size = t.size();
    size_t i{size};
    for (unsigned char c : t) {
        if (!isFour(c)) {
            throw std::logic_error("Four digit can't be more than 3");
        }
        number[--i] = c;
    }
}

Four::Four(const std::string t) {
    size = t.size();
    number = new unsigned char[size];
    for (size_t i = size - 1, j = 0; j < size; i--, j++) {
        if (!isFour(t[i])) {
            throw std::logic_error("Four digit can't be more than 3");
        }
        number[i] = t[j];
    }
}

Four::Four(const Four &other) {
    size = other.size;
    number = new unsigned char[size];
    for (size_t i = 0; i < size; i++) {
        number[i] = other.number[i];
    }
}

Four::Four(Four &&other) noexcept {
    size = other.size;
    number = other.number;  
    other.size = 0;
    other.number = nullptr;
}

Four Four::operator=(const Four &other) {
    if (&other != this) {
        delete[] number;
        size = other.size;
        number = new unsigned char[size];
        for (size_t i = 0; i < size; i++) {
            number[i] = other.number[i];
        }
    }
    return *this;
}

Four Four::operator+(const Four &other) const {
    size_t resultSize = std::max(other.size, size) + 1;
    std::string result(resultSize, '0');
    int carry = 0;
    for (size_t i = 0; i < resultSize; i++) {
        int d1 = (i < size) ? (number[i] - '0') : 0;
        int d2 = (i < other.size) ? (other.number[i] - '0') : 0;
        int sum = d1 + d2 + carry;
        result[i] = (sum % 4) + '0';
        carry = sum / 4;
    }
    if (carry > 0) {
        result[resultSize - 1] = carry + '0';
    }
    if (result[resultSize - 1] == '0') {
        result.erase(resultSize - 1, 1);
    }
    std::reverse(result.begin(), result.end());
    return Four(result);
}

Four Four::operator-(const Four &other) const {
    if (*this < other) {
        throw std::logic_error("Difference can't be negative");
    }
    size_t resultSize = std::max(other.size, size) + 1;
    std::string result(resultSize, '0');
    int carry = 0;
    for (size_t i = 0; i < resultSize; i++) {
        int d1 = (i < size) ? (number[i] - '0') : 0;
        int d2 = (i < other.size) ? (other.number[i] - '0') : 0;

        int diff = d1 - d2 - carry;
        if (diff < 0) {
            diff += 4;
            carry = 1;
        }
        else {
            carry = 0;
        }
        result[i] = diff + '0';
    }
    if (result[resultSize - 1] == '0') {
        result.erase(resultSize - 1, 1);
    }
    std::reverse(result.begin(), result.end());
    return Four(result);
}

bool Four::operator==(const Four &other) const {
    if (&other == this) {
        return true;
    }
    if (size != other.size) {
        return false;
    }
    for (size_t i = 0; i < size; i++) {
        if (number[i] != other.number[i]) {
            return false;
        }
    }
    return true;
}

bool Four::operator!=(const Four &other) const {
    if (*this == other) {
        return false;
    }
    return true;
}

bool Four::operator<(const Four &other) const {
    if (&other == this) {
        return false;
    }

    if (size < other.size) {
        return true;
    }
    else if (size > other.size) {
        return false;
    }
    else {
        for (size_t i = size; i--;) {
            if (number[i] < other.number[i]) {
                return true;
            }
            else if (number[i] > other.number[i]) {
                return false;
            }
            else {
                continue;
            }
        }
        return false;
    }
}

bool Four::operator<=(const Four &other) const {
    if (*this > other) {
        return false;
    }
    return true;
}

bool Four::operator>(const Four other) const {
    if (*this < other || *this == other) {
        return false;
    }
    return true;
}

bool Four::operator>=(const Four other) const {
    if (*this < other) {
        return false;
    }
    return true;
}

std::ostream &Four::print(std::ostream &os) {
    for (size_t i = size; i--;) {
        os << number[i];
    }
    return os;
}

Four::~Four() noexcept {
    if (size > 0) {
        size = 0;
        delete[] number;
        number = nullptr;
    }
}