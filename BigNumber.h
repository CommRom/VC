#ifndef VC_BIGNUMBER_H
#define VC_BIGNUMBER_H

#include <string>

const int MAX_DIGITS = 200;

class BigNumber {
private:
    char digits[MAX_DIGITS];
    bool isNegative;

public:
    // Konstruktor
    BigNumber();

    // Nastaví hodnotu BigNumber z řetězce
    void setFromString(const char *str);

    // Převod BigNumber na řetězec
    std::string toString() const;

    //Funkce, která vrací true, pokud je první číslo větší než druhé
    bool operator>(const BigNumber &other) const;

    // Operátor pro sčítání
    BigNumber operator+(const BigNumber &other) const;

    // Operátor pro odčítání
    BigNumber operator-(const BigNumber &other) const;

    // Operátor pro násobení
    BigNumber operator*(const BigNumber &other) const;


};

#endif //VC_BIGNUMBER_H
