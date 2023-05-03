#ifndef Fraction_HPP
#define Fraction_HPP
#include <cmath>
#include <math.h>
#include <string>
#include <stdexcept>
using namespace std;

namespace ariel{
class Fraction{
    public:
        Fraction();
        Fraction(int, int);
        Fraction(float);
        ~Fraction(); // Destructor
        Fraction(const Fraction& other); // Copy constructor
        Fraction(Fraction&& other) noexcept; // Move constructor
     
        int numerator;
        int denominator;

        int getNumerator();
        int getDenominator();
        
    // -------------- Operation with Fraction --------------
        Fraction& operator=(const Fraction& fraction2);
        Fraction& operator=(Fraction&& fraction2) noexcept;
        Fraction operator+(const Fraction& fraction2);
        Fraction operator-(const Fraction& fraction2);
        Fraction operator/(const Fraction& fraction2);
        Fraction operator*(const Fraction& fraction2);

        bool operator>(const Fraction& fraction2);
        bool operator>=(const Fraction& fraction2);
        bool operator<(const Fraction& fraction2);
        bool operator<=(const Fraction& fraction2);
        bool operator==(const Fraction& fraction2);

        // ---- Prefix ----
        Fraction operator++();
        Fraction operator--();

        // ---- Postfix ----
        Fraction operator++(int);
        Fraction operator--(int);
        
        // ---- Friend ----
        friend std::ostream& operator<<(std::ostream& ost, const Fraction &frac);
        friend std::istream& operator>>(std::istream& cin, Fraction& frac);
        friend bool operator>(const Fraction&, const Fraction&);
        friend bool operator>=(const Fraction&, const Fraction&);
        friend bool operator<(const Fraction&, const Fraction&);
        friend bool operator<=(const Fraction&, const Fraction&);
        friend bool operator==(const Fraction&, const Fraction&);

    // -------------- Operation with float --------------
        Fraction operator+(const float& num);
        Fraction operator-(const float& num);
        Fraction operator/(const float& num);
        Fraction operator*(const float& num);

        bool operator>(float);
        bool operator>=(float);
        bool operator<(float);
        bool operator<=(float);
        bool operator==(float);

        // ---- Friend ----
        friend Fraction operator+(float num, const Fraction& frac);
        friend Fraction operator-(float num, const Fraction& frac);
        friend Fraction operator/(float num, const Fraction& frac);
        friend Fraction operator*(float num, const Fraction& frac);

        friend bool operator>(float num, const Fraction& frac);
        friend bool operator>=(float num, const Fraction& frac);
        friend bool operator<(float num, const Fraction& frac);
        friend bool operator<=(float num, const Fraction& frac);
        friend bool operator==(float, const Fraction& frac);

};
};
#endif