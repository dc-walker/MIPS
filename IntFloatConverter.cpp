#include "IntFloatConverter.h"

// 辅助函数：补齐补码长度
void padString(std::string& str, int length, char flag) 
{
    if(flag == '1')
    {
        while (str.length() < length) 
            str = "1" + str;
    }
    else
    {
        while (str.length() < length) 
            str = "0" + str;
    }
}

// 整数加法
std::string addInt(const std::string& a, const std::string& b) 
{
    std::string result;
    int carry = 0;

    // 补齐字符串长度
    int len = 32;
    std::string operandA = a;
    std::string operandB = b;
    padString(operandA, len, operandA[0]);
    padString(operandB, len, operandB[0]);

    // 从右向左逐位相加
    for (int i = len - 1; i >= 0; i--)
    {
        int sum = (operandA[i] - '0') + (operandB[i] - '0') + carry;
        result = static_cast<char>((sum % 2) + '0') + result;
        carry = sum / 2;
    }

    // 若最高位有进位，补上1(若均为32位则不考虑)
    // if (carry != 0) 
    // {
    //     result = "1" + result;
    // }
    return result;
}

// 整数减法
std::string subInt(const std::string& a, const std::string& b) 
{    
    // 补齐字符串长度
    int len = 32;
    std::string operandA = a;
    std::string operandB = b;
    padString(operandA, len, operandA[0]);
    padString(operandB, len, operandB[0]);

    int tmp = -binToInt(operandB);
    std::string complementB = intToBin(tmp);   //计算出B的补码
    return addInt(operandA, complementB);
}

// 整数乘法
std::string multiplyInt(const std::string& a, const std::string& b)
{
    std::string result = "0";

    // 补齐字符串长度
    int len = 32;
    std::string operandA = a;
    std::string operandB = b;
    padString(operandA, len, operandA[0]);
    padString(operandB, len, operandB[0]);

    // 从右向左逐位相乘，并累加部分乘积
    for (int i = len - 1; i >= 0; --i)
    {
        if (operandB[i] == '1') 
        {
            std::string partialProduct = operandA;
            for(int j = len - 1; j > i; j--)
            {
                partialProduct = partialProduct.substr(1) + "0";
            }
            // 如果长度不够则需补齐
            padString(partialProduct, len, '0');

            result = addInt(result, partialProduct);
        }
    }

    return result;
}

// 整数除法
std::string divideInt(const std::string& a, const std::string& b) 
{
    if (binToInt(b) == 0) 
        return "NaN( The divisor cannot be 0! )";

    // 补齐字符串长度
    int len = 32;
    std::string operandA = a;
    std::string operandB = b;
    padString(operandA, len, operandA[0]);
    padString(operandB, len, operandB[0]);
    
    int dividend = binToInt(a);
    int divisor = binToInt(b);
    
    std::string quotient = intToBin(dividend  / divisor);

    std::string result = "";
    std::string reminder = "";   //上一位的余数留到下一位

    for(int i = 0; i < len; i++)
    {
        reminder += operandA[i];
        int quo = 0; // 按位除的商
        std::string tmp = subInt(reminder, operandB);
        if(tmp[0] == '0')   // 减完后还是正数
        {
            reminder = tmp;
            quo++;
        }
        result += char(quo + '0');
    }
    
    return quotient;
}

// 打印浮点数的二进制码
void printFloatBin(const FloatConverter& converter) 
{
    std::cout << "Binary representation: " << converter.sign << " "
              << converter.exponent << " " << converter.fraction << std::endl;
}

// 整数转补码
std::string intToBin(int integer, int numBits) 
{
    std::string binary = "";
    unsigned int mask = 1;  // 掩码
    for (int i = 0; i < numBits; i++)
    {
        binary = ((integer & mask) > 0 ? "1" : "0") + binary;
        mask <<= 1;  // 掩码左移一位
    }

    return binary;
}

// 补码转整数
int binToInt(const std::string& complement, int numBits) 
{
    int num = 0;
    unsigned int mask = 1 << (numBits - 1);  // 掩码

    for (char c : complement) 
    {
        if (c == '1') {
            num |= mask;
        }
        mask >>= 1;  // 右移掩码以设置下一位
    }

    // 如果传进来的是负数，需要把前面的位全部置为1
    if(complement[0] == '1')   
    {
        mask = 1 << 31;
        for(int i = 0; i < 32 - numBits; i++)
        {
            num |= mask;
            mask >>= 1;
        }
    } 

    return num;
}

// 浮点数转二进制码
FloatConverter floatToBin(float number) 
{
    FloatConverter converter;

    if (number == 0) 
    {
        converter.sign = "0";
        converter.exponent = std::string(8, '0');
        converter.fraction = std::string(23, '0');
        return converter;
    }
     
    if ( std::isnan(number) )  // NaN
    {
        converter.sign = "0";
        converter.exponent = std::string(8, '1');
        converter.fraction = std::string(23, '1');
        return converter;
    }

    converter.sign = number < 0 ? "1" : "0";

    float normalized = std::abs(number);
    int exponent = 0;

    while (normalized >= 2.0) 
    {
        normalized /= 2;
        exponent++;
    }

    while (normalized < 1.0) 
    {
        normalized *= 2;
        exponent--;
    }

    int biasedExponent = exponent + 127;
    converter.exponent = intToBin(biasedExponent, 8);

    // std::cout << biasedExponent << " a " << converter.exponent << std::endl;

    int fractionBits = 23;
    converter.fraction = std::string(23, '0');

    // 将小数部分转化为二进制
    normalized -= 1;
    while (normalized > 0 && fractionBits > 0) 
    {
        normalized *= 2;
        if (normalized >= 1) 
        {
            converter.fraction[23 - fractionBits] = '1';
            normalized -= 1;
        }
        fractionBits--;
    }

    return converter;
}

float binToFloat(const FloatConverter& converter) 
{
    // e全为 1，f全为 0
    if (converter.exponent == std::string(8, '1') && converter.fraction == std::string(23, '0')) 
    {
        if (converter.sign == "1") 
            return -INFINITY;
         else 
            return INFINITY;
    } 
    else if (converter.exponent == std::string(8, '1') && converter.fraction != std::string(23, '0')) 
        //e全为1，f不全为0
        return NAN;
    else if (converter.exponent == std::string(8, '0') && converter.fraction == std::string(23, '0'))
        return 0.0;

    int biasedExponent = 0;
    for (int i = 0; i < 8; ++i) {
        biasedExponent *= 2;
        biasedExponent += (converter.exponent[i] == '1') ? 1 : 0;
    }
    biasedExponent -= 127;

    float value = 1.0;
    float fraction = 0.5;

    for (int i = 0; i < 23; ++i) {
        if (converter.fraction[i] == '1') {
            value += fraction;
        }
        fraction *= 0.5f;
    }

    value *= std::pow(2, biasedExponent);
    if (converter.sign == "1") {
        value = -value;
    }

    return value;
}

FloatConverter addFloats(const FloatConverter& a, const FloatConverter& b) 
{
    FloatConverter result;

    float floatA = binToFloat(a);
    float floatB = binToFloat(b);

    float floatResult = floatA + floatB;

    result = floatToBin(floatResult);

    return result;
}

FloatConverter subtractFloats(const FloatConverter& a, const FloatConverter& b) 
{
    FloatConverter result;

    float floatA = binToFloat(a);
    float floatB = binToFloat(b);

    float floatResult = floatA - floatB;

    result = floatToBin(floatResult);

    return result;
}

FloatConverter multiplyFloats(const FloatConverter& a, const FloatConverter& b) 
{
    FloatConverter result;

    float floatA = binToFloat(a);
    float floatB = binToFloat(b);

    float floatResult = floatA * floatB;

    result = floatToBin(floatResult);

    return result;
}

FloatConverter divideFloats(const FloatConverter& a, const FloatConverter& b) 
{
    FloatConverter result;

    float floatA = binToFloat(a);
    float floatB = binToFloat(b);

    float floatResult = floatA / floatB;

    result = floatToBin(floatResult);

    return result;
}
