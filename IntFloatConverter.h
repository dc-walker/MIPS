#ifndef _INTFLOATCONVERTER_H
#define _INTFLOATCONVERTER_H

#include <iostream>
#include <cmath>
#include <string>

struct FloatConverter {
    std::string sign;
    std::string exponent;
    std::string fraction;
};


void padString(std::string& str, int length, char flag);
std::string intToBin(int integer, int numBits = 32);
int binToInt(const std::string& complement, int numBits = 32);
std::string addInt(const std::string& a, const std::string& b);
std::string subInt(const std::string& a, const std::string& b);
std::string multiplyInt(const std::string& a, const std::string& b);
std::string divideInt(const std::string& a, const std::string& b);

void printFloatBin(const FloatConverter& converter);
FloatConverter floatToBin(float number);
float binToFloat(const FloatConverter& converter);
FloatConverter addFloats(const FloatConverter& a, const FloatConverter& b);
FloatConverter subtractFloats(const FloatConverter& a, const FloatConverter& b);
FloatConverter multiplyFloats(const FloatConverter& a, const FloatConverter& b);
FloatConverter divideFloats(const FloatConverter& a, const FloatConverter& b);


# endif