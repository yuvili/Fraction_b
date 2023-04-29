#include <iostream>
#include <cmath>
#include<math.h>
#include "Fraction.hpp"
#include <string>
#include<stdexcept>
#include <bits/stdc++.h>
using namespace std;

namespace ariel{
    // greatest common divisor
    int gcd(int num1, int num2){
        if(num1 == 0){
            return num2;
        }
        return gcd(num2%num1, num1);
    }

    void simpler(int& numer, int& denom){
        int gcdRes = gcd(numer, denom);
        
        numer = numer / gcdRes;
        if(numer == 0 && denom < 0){
            denom = denom;
        }
        else {
            denom = denom / gcdRes;
        }
    }

    Fraction::Fraction() {}

    Fraction::Fraction(int number1, int number2){
        if(number2 == 0 && number1 != 0){
            throw std::invalid_argument("Can't devide by 0.");
        }
        
        numerator = number1;
        denominator = number2;
        simpler(numerator, denominator);
        if(denominator < 0 && numerator > 0){
            numerator *= (-1);
            denominator *= (-1);
        }
        
    }

    Fraction::Fraction(float number){
        if(number == 0){
            numerator = 0;
            denominator = 0;
        }
        else{
            number = floor(1000*number)/1000; // ignore digit after 3 beyond the desimal point

            // Fetch integral value of the decimal
            double intVal = floor(number);
        
            // Fetch fractional part of the decimal
            double fVal = number - intVal;
        
            // Consider precision value to
            // convert fractional part to
            // integral equivalent
            const int pVal = 1000;
        
            // Calculate GCD of integral
            // equivalent of fractional
            // part and precision value
            int gcdVal = gcd((int)round(fVal * pVal), pVal);
        
            // Calculate num and deno
            denominator = pVal / gcdVal;
            numerator = (intVal * denominator) + round(fVal * pVal) / gcdVal;
        }
    }

    Fraction::~Fraction(){}

    Fraction::Fraction(const Fraction& other){
        numerator = other.numerator;
        denominator = other.denominator;
    }

    Fraction::Fraction(Fraction&& other) noexcept{
        numerator = other.numerator;
        denominator = other.denominator;
    }

    int Fraction::getNumerator(){
        return numerator;
    }
    int Fraction::getDenominator(){
        return denominator;
    }

    // -------------- Operation with Fraction --------------

    Fraction& Fraction::operator=(const Fraction& fraction2){
        if(this != &fraction2){
            numerator = fraction2.numerator;
            denominator = fraction2.denominator;
        }
        return *this;
    }

    Fraction& Fraction::operator=(Fraction&& fraction2) noexcept{
        if(this != &fraction2){
            numerator = fraction2.numerator;
            denominator = fraction2.denominator;
        }
        return *this;
    }

    Fraction Fraction::operator+(const Fraction& fraction2){
        float number1 = (numerator == 0) ? 0.0 : ((float)numerator/(float)denominator);
        float number2 = (fraction2.numerator == 0) ? 0.0 : ((float)fraction2.numerator/(float)fraction2.denominator);

        if((number1 + number2) > std::numeric_limits<float>::max()){
            throw std::overflow_error("Result is too big.");
        }
        if((number1 + number2) < std::numeric_limits<int>::min()){
            throw std::overflow_error("Result is too small.");
        }

        int gcdRes = gcd(denominator, fraction2.denominator);
        int common_divider = (denominator*fraction2.denominator)/gcdRes;
        int newNumerator = (numerator*(common_divider/denominator)) + (fraction2.numerator*(common_divider/fraction2.denominator));
        return Fraction(newNumerator, common_divider);
    }

    Fraction Fraction::operator-(const Fraction& fraction2){
        int gcdRes = gcd(denominator, fraction2.denominator);
        int common_divider = (denominator*fraction2.denominator)/gcdRes;
        int newNumerator = (numerator*(common_divider/denominator)) - (fraction2.numerator*(common_divider/fraction2.denominator));
        if(newNumerator/common_divider>std::numeric_limits<int>::max()){
            throw std::overflow_error("Result is too big.");
        }
        if(newNumerator/common_divider<std::numeric_limits<int>::min()){
            throw std::overflow_error("Result is too small.");
        }

        return Fraction(newNumerator, common_divider);
    }

    Fraction Fraction::operator/(const Fraction& fraction2){
        if(fraction2.numerator == 0){
            throw std::runtime_error("Can't devide by 0");
        }

        int newNumerator = numerator*fraction2.denominator;
        int newDenom = denominator*fraction2.numerator;

         if(newNumerator/newDenom>std::numeric_limits<int>::max()){
            throw std::overflow_error("Result is too big.");
        }
        if(newNumerator/newDenom<std::numeric_limits<int>::min()){
            throw std::overflow_error("Result is too small.");
        }

        return Fraction(newNumerator, newDenom);
    }

    Fraction Fraction::operator*(const Fraction& fraction2){
        int newNumerator = numerator*fraction2.numerator;
        int newDenom = denominator*fraction2.denominator;
        
        if(newNumerator/newDenom>std::numeric_limits<int>::max()){
            throw std::overflow_error("Result is too big.");
        }
        if(newNumerator/newDenom<std::numeric_limits<int>::min()){
            throw std::overflow_error("Result is too small.");
        }

        return Fraction(newNumerator, newDenom);
    }

    bool Fraction::operator>(const Fraction& fraction2){
        float number1 = (numerator == 0) ? 0.0 : ((float)numerator/(float)denominator);
        float number2 = (fraction2.numerator == 0) ? 0.0 : ((float)fraction2.numerator/(float)fraction2.denominator);
        return number1 > number2;
    }

    bool Fraction::operator>=(const Fraction& fraction2){
        float number1 = (numerator == 0) ? 0.0 : ((float)numerator/(float)denominator);
        float number2 = (fraction2.numerator == 0) ? 0.0 : ((float)fraction2.numerator/(float)fraction2.denominator);
        return number1 >= number2;
    }

    bool Fraction::operator<(const Fraction& fraction2){
        float number1 = (numerator == 0) ? 0.0 : ((float)numerator/(float)denominator);
        float number2 = (fraction2.numerator == 0) ? 0.0 : ((float)fraction2.numerator/(float)fraction2.denominator);
        return number1 < number2;
    }

    bool Fraction::operator<=(const Fraction& fraction2){
        float number1 = (numerator == 0) ? 0.0 : ((float)numerator/(float)denominator);
        float number2 = (fraction2.numerator == 0) ? 0.0 : ((float)fraction2.numerator/(float)fraction2.denominator);
        return number1 <= number2;
    }

    bool Fraction::operator==(const Fraction& fraction2){
        float number1 = (numerator == 0) ? 0.0 : ((float)numerator/(float)denominator);
        float number2 = (fraction2.numerator == 0) ? 0.0 : ((float)fraction2.numerator/(float)fraction2.denominator);
        return number1 == number2;
    }

    // ---- Prefix ----
    Fraction Fraction::operator++(){
        numerator = numerator + denominator;
        simpler(numerator, denominator);
        return Fraction(numerator, denominator);
    }

    Fraction Fraction::operator--(){
        numerator = numerator - denominator;
        simpler(numerator, denominator);
        return Fraction(numerator, denominator);
    }

    // ---- Postfix ----
    Fraction Fraction::operator--(int){
        int oldNum = numerator;
        int oldDenom= denominator;
        numerator -= denominator;
        simpler(numerator, denominator);
        return Fraction(oldNum, oldDenom);
    }

     Fraction Fraction::operator++(int){
        int oldNum = numerator;
        int oldDenom= denominator;
        numerator += denominator;
        simpler(numerator, denominator);
        return Fraction(oldNum, oldDenom);
    }

    // ---- Friend ----
    std::ostream &operator<<(std::ostream& ost, const Fraction& frac){
        ost << frac.numerator << "/" << frac.denominator;
        return ost;
    }

    std::istream &operator>>(std::istream& cin, Fraction& frac){
        int inputNumer, inputDeno;
        if(!(cin >> inputNumer >> inputDeno)){
            throw std::runtime_error("Invalid input. Please enter two integers separated by a space.");
        }
        if(inputDeno == 0 && inputNumer != 0){
            throw std::runtime_error("Invalid input. Can't divide by 0.");
        }
        frac = Fraction(inputNumer, inputDeno);
        return cin;
    }

    bool operator>(const Fraction& frac1, const Fraction& frac2){
        float number1 = (frac1.numerator == 0) ? 0.0 : ((float)frac1.numerator/(float)frac1.denominator);
        float number2 = (frac2.numerator == 0) ? 0.0 : ((float)frac2.numerator/(float)frac2.denominator);
        return number1 > number2;
    }

    bool operator>=(const Fraction& frac1, const Fraction& frac2){
        float number1 = (frac1.numerator == 0) ? 0.0 : ((float)frac1.numerator/(float)frac1.denominator);
        float number2 = (frac2.numerator == 0) ? 0.0 : ((float)frac2.numerator/(float)frac2.denominator);
        return number1 >= number2;
    }

    bool operator<(const Fraction& frac1, const Fraction& frac2){
        float number1 = (frac1.numerator == 0) ? 0.0 : ((float)frac1.numerator/(float)frac1.denominator);
        float number2 = (frac2.numerator == 0) ? 0.0 : ((float)frac2.numerator/(float)frac2.denominator);
        return number1 < number2;
    }

    bool operator<=(const Fraction& frac1, const Fraction& frac2){
        float number1 = (frac1.numerator == 0) ? 0.0 : ((float)frac1.numerator/(float)frac1.denominator);
        float number2 = (frac2.numerator == 0) ? 0.0 : ((float)frac2.numerator/(float)frac2.denominator);
        return number1 <= number2;
    }

    bool operator==(const Fraction& frac1, const Fraction& frac2){
        float number1 = (frac1.numerator == 0) ? 0.0 : ((float)frac1.numerator/(float)frac1.denominator);
        float number2 = (frac2.numerator == 0) ? 0.0 : ((float)frac2.numerator/(float)frac2.denominator);
        return number1 == number2;
    }

    // -------------- Operation with float --------------
    Fraction Fraction::operator+(const float& num){
        if(num == 0){
            return Fraction(numerator, denominator);
        }
        float number = floor(1000*num)/1000; // ignore digit after 3 beyond the desimal point

        float fractionFloat = (float)numerator/(float)denominator;
        float result = fractionFloat + number;
        return Fraction(result);
    }

    Fraction Fraction::operator-(const float& num){
        if(num == 0){
            return Fraction(numerator, denominator);
        }

        float number = floor(1000*num)/1000; // ignore digit after 3 beyond the desimal point

        float fractionFloat = (float)numerator/(float)denominator;
        float result = fractionFloat - number;
        return Fraction(result);
    }

    Fraction Fraction::operator/(const float& num){
        if(num == 0){
            throw std::runtime_error("Can't devide by 0");
        }

        Fraction numFract(num);
        int newNumerator = numerator * numFract.denominator;
        int newDenom = denominator * numFract.numerator;

        simpler(newNumerator, newDenom);
        return Fraction(newNumerator, newDenom);
    }

    Fraction Fraction::operator*(const float& num){
        if(num == 0){
            return Fraction(0, 0);
        }
        Fraction numFract(num);
        int newNumerator = numerator * numFract.numerator;
        int newDenom = denominator * numFract.denominator;

        simpler(newNumerator, newDenom);
        return Fraction(newNumerator, newDenom);
    }

    bool Fraction::operator>(const float num){
        float result = (float)numerator/(float)denominator;
        return result > num;
    }

    bool Fraction::operator>=(const float num){
        float result = (float)numerator/(float)denominator;
        return result >= num;
    }

    bool Fraction::operator<(const float num){
        float result = (float)numerator/(float)denominator;
        return result < num;
    }

    bool Fraction::operator<=(const float num){
        float result = (float)numerator/(float)denominator;
        return result <= num;
    }

    bool Fraction::operator==(const float num){
        float result = (float)numerator/(float)denominator;
        return result == num;
    }

    // ---- Friend ----
    Fraction operator+(float num, const Fraction& frac){
        if(num == 0){
            return Fraction(frac.numerator, frac.denominator);
        }
        float fractionFloat = (float)frac.numerator/(float)frac.denominator;
        float result = fractionFloat + num;
        return Fraction(result);
    }

    Fraction operator-(float num, const Fraction& frac){
        if(num == 0){
            int newNumerator = 0 - frac.numerator;
            return Fraction(newNumerator, frac.denominator);
        }
        float fractionFloat = (float)frac.numerator/(float)frac.denominator;
        float result = num - fractionFloat;
        return Fraction(result);
    }

    Fraction operator/(float num, const Fraction& frac){
        if(num == 0){
            return Fraction(0, 0);
        }

        Fraction numFract(num);
        int newNumerator = frac.denominator * numFract.numerator;
        int newDenom = frac.numerator * numFract.denominator;

        simpler(newNumerator, newDenom);
        return Fraction(newNumerator, newDenom);
    }

    Fraction operator*(float num, const Fraction& frac){
        if(num == 0){
            return Fraction(0, 0);
        }
        Fraction numFract(num);
        int newNumerator = frac.numerator * numFract.numerator;
        int newDenom = frac.denominator * numFract.denominator;

        simpler(newNumerator, newDenom);
        return Fraction(newNumerator, newDenom);
    }

    bool operator>(float num, const Fraction& frac){
        float result = (float)frac.numerator/(float)frac.denominator;
        return num > result;
    }

    bool operator>=(float num, const Fraction& frac){
        float result = (float)frac.numerator/(float)frac.denominator;
        return num >= result;
    }

    bool operator<(float num, const Fraction& frac){
        float result = (float)frac.numerator/(float)frac.denominator;
        return num < result;
    }

    bool operator<=(float num, const Fraction& frac){
        float result = (float)frac.numerator/(float)frac.denominator;
        return num <= result;
    }

    bool operator==(const float num, const Fraction& frac){
        float result = (float)frac.numerator/(float)frac.denominator;
        return result == num;
    }
}