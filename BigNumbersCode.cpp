#include "BigNumber.h"
#include <iostream>

using namespace std;

BigNumber::BigNumber() {
    for (int i = 0; i < MAX_DIGITS; ++i) {
        digits[i] = 0;
    }
    isNegative = false;
}

void BigNumber::setFromString(const char *str) {
    isNegative = (str[0] == '-');

    // Inicializace pole číslic
    for (int i = 0; i < MAX_DIGITS; ++i) {
        digits[i] = 0;
    }

    // Naplnění pole číslic
    int len = 0;
    if(isNegative){
        while (str[len+1] >= '0' && str[len+1] <= '9') {
            ++len;
        }
        ++len;
    }
    else {
        while (str[len] >= '0' && str[len] <= '9') {
            ++len;
        }
    }

    int index = 0;
    if(isNegative){
        for (int i = len-1; i >= 1; --i) {
            digits[index++] = str[i] - '0';
        }
    }
    else {
        for (int i = len - 1; i >= 0; --i) {
            digits[index++] = str[i] - '0';
        }
    }
}
// Převede BigNumber na řetězec
std::string BigNumber::toString() const {
    string result;

    if (isNegative) {
        result.push_back('-');
    }

    bool nonZeroFound = false;

    for (int i = MAX_DIGITS - 1; i >= 0; --i) {
        if (digits[i] != 0  || nonZeroFound) {
            result.push_back(digits[i] + '0');
            nonZeroFound = true;
        }
    }


    if (!nonZeroFound) {
        result.push_back('0');
    }

    return result;
}

bool BigNumber::operator>(const BigNumber& other) const {
    for (int i = MAX_DIGITS - 1; i >= 0; --i) {
        if (digits[i] > other.digits[i])
            return true;
        else if (digits[i] < other.digits[i])
            return false;
    }
}

BigNumber BigNumber::operator*(const BigNumber& other) const {
    BigNumber result;

    for (int i = 0; i < MAX_DIGITS/2; ++i) {
        int carry = 0;

        for (int j = 0; j < MAX_DIGITS/2; ++j) {
            int product = result.digits[i + j] + digits[i] * other.digits[j] + carry;
            result.digits[i + j] = product % 10;
            carry = product / 10;
        }
    }

    if(isNegative ^ other.isNegative){
        result.isNegative = true;
    }

    return result;
}

/*BigNumber BigNumber::reduction(const BigNumber& other) const {
    BigNumber result;
    int borrow = 0;

    for (int i = 0; i < MAX_DIGITS; ++i) {
    int diff = digits[i] - other.digits[i] - borrow;
    if (diff < 0) {
    diff += 10;
    borrow = 1;
    } else {
        borrow = 0;
    }
    result.digits[i] = diff;
    }

    return result;
}*/

BigNumber BigNumber::operator+(const BigNumber& other) const {
    BigNumber result;
    int carry = 0;

    if (*this > other) {
        if (!isNegative && other.isNegative) {
            int borrow = 0;

            for (int i = 0; i < MAX_DIGITS; ++i) {
                int diff = digits[i] - other.digits[i] - borrow;
                if (diff < 0) {
                    diff += 10;
                    borrow = 1;
                } else {
                    borrow = 0;
                }
                result.digits[i] = diff;
            }
            return result;;
        } else if (isNegative && !other.isNegative) {
            result.isNegative = true;
            int borrow = 0;

            for (int i = 0; i < MAX_DIGITS; ++i) {
                int diff = digits[i] - other.digits[i] - borrow;
                if (diff < 0) {
                    diff += 10;
                    borrow = 1;
                } else {
                    borrow = 0;
                }
                result.digits[i] = diff;
            }
            return result;
        }
    }
        else {
            if (isNegative && !other.isNegative) {
                int borrow = 0;

                for (int i = 0; i < MAX_DIGITS; ++i) {
                    int diff = other.digits[i] - digits[i] - borrow;
                    if (diff < 0) {
                        diff += 10;
                        borrow = 1;
                    } else {
                        borrow = 0;
                    }
                    result.digits[i] = diff;
                }

                return result;
            } else if (!isNegative && other.isNegative) {
                result.isNegative = true;
                int borrow = 0;

                for (int i = 0; i < MAX_DIGITS; ++i) {
                    int diff = other.digits[i] - digits[i] - borrow;
                    if (diff < 0) {
                        diff += 10;
                        borrow = 1;
                    } else {
                        borrow = 0;
                    }
                    result.digits[i] = diff;
                }

                return result;
            }
        }

        for (int i = 0; i < MAX_DIGITS; ++i) {
            int sum = digits[i] + other.digits[i] + carry;
            result.digits[i] = sum % 10;
            carry = sum / 10;
        }

        if (isNegative && other.isNegative) {
            result.isNegative = true;
        }

        return result;
    }




    BigNumber BigNumber::operator-(const BigNumber &other) const {
        BigNumber result;
        int borrow = 0;

        if (*this > other) {
            if (!isNegative && other.isNegative) {
                int carry = 0;

                for (int i = 0; i < MAX_DIGITS; ++i) {
                    int sum = digits[i] + other.digits[i] + carry;
                    result.digits[i] = sum % 10;
                    carry = sum / 10;
                }

                return result;
            } else if (isNegative && !other.isNegative) {
                result.isNegative = true;
                int carry = 0;

                for (int i = 0; i < MAX_DIGITS; ++i) {
                    int sum = digits[i] + other.digits[i] + carry;
                    result.digits[i] = sum % 10;
                    carry = sum / 10;
                }

                result.isNegative = true;


                return result;
            } else if (isNegative && other.isNegative) {
                result.isNegative = true;
            }
        } else {
            if (isNegative && !other.isNegative) {
                int carry = 0;

                for (int i = 0; i < MAX_DIGITS; ++i) {
                    int sum = digits[i] + other.digits[i] + carry;
                    result.digits[i] = sum % 10;
                    carry = sum / 10;
                }

                result.isNegative = true;

                return result;
            } else if (!isNegative && other.isNegative) {
                int carry = 0;

                for (int i = 0; i < MAX_DIGITS; ++i) {
                    int sum = digits[i] + other.digits[i] + carry;
                    result.digits[i] = sum % 10;
                    carry = sum / 10;
                }

                return result;
            } else if (isNegative && other.isNegative) {
                for (int i = 0; i < MAX_DIGITS; ++i) {
                    int diff = other.digits[i] - digits[i] - borrow;
                    if (diff < 0) {
                        diff += 10;
                        borrow = 1;
                    } else {
                        borrow = 0;
                    }
                    result.digits[i] = diff;
                }

                return result;
            }
            else if(!isNegative && !other.isNegative){
                int borrow = 0;

                for (int i = 0; i < MAX_DIGITS; ++i) {
                    int diff = other.digits[i] - digits[i] - borrow;
                    if (diff < 0) {
                        diff += 10;
                        borrow = 1;
                    } else {
                        borrow = 0;
                    }
                    result.digits[i] = diff;
                }
                result.isNegative = true;

                return result;
            }

        }
        for (int i = 0; i < MAX_DIGITS; ++i) {
            int diff = digits[i] - other.digits[i] - borrow;
            if (diff < 0) {
                diff += 10;
                borrow = 1;
            } else {
                borrow = 0;
            }
            result.digits[i] = diff;
        }

        return result;
    }

