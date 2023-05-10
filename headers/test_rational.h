//
// Created by comme on 5/10/2023.
//

#ifndef YELLOW_BELT_CPP_TEST_RATIONAL_H
#define YELLOW_BELT_CPP_TEST_RATIONAL_H

#include <exception>
#include <stdexcept>
#include <iostream>
#include "test_framework.h"

class Rational {
public:
    Rational() {
        numerator = 0;
        denominator = 1;
    }

    Rational(int numerator_, int denominator_) {
        if(denominator_ == 0)
            throw std::invalid_argument("Invalid argument");
        bool numerator_positive = numerator_ > 0;
        bool denominator_positive = denominator_ > 0;

        int a_num = abs(numerator_);
        int a_den = abs(denominator_);

        shorten_for_common(a_num, a_den);

        numerator = a_num;
        denominator = a_den;

        numerator = numerator_positive ? numerator : -numerator;
        denominator = denominator_positive ? denominator : -denominator;

        if(denominator < 0){
            denominator = -denominator;
            numerator = -numerator;
        }

        if(numerator == 0){
            denominator = 1;
        }

    }

    int Numerator() const {
        return numerator;
    }

    int Denominator() const {
        return denominator;
    }

    Rational operator+(const Rational& rhs){
        if(this->denominator == rhs.denominator) {
            this->numerator += rhs.numerator;
            return {this->numerator, this->denominator};
        }else{
            int common_multiple = lcm(this->denominator, rhs.denominator);
            int left_to_multiply = common_multiple / this->denominator;
            int right_to_multiply = common_multiple / rhs.denominator;
            this->numerator *= left_to_multiply;
            int right_numerator = rhs.numerator * right_to_multiply;
            int res = this->numerator + right_numerator;
            return {res, common_multiple};
        }
    }

    Rational operator-(const Rational& rhs){
        if(this->denominator == rhs.denominator)
            this->numerator -= rhs.numerator;
        else{
            int common_multiple = lcm(this->denominator, rhs.denominator);
            int left_to_multiply = common_multiple / this->denominator;
            int right_to_multiply = common_multiple / rhs.denominator;
            this->numerator *= left_to_multiply;
            int right_numerator = rhs.numerator * right_to_multiply;
            int res = this->numerator - right_numerator;
            return {res, common_multiple};
        }
        return {this->numerator, this->denominator};
    }

    Rational operator*(const Rational& rhs) const{
        return {this->numerator * rhs.numerator, this->denominator * rhs.denominator};
    }

    Rational operator/(const Rational& rhs)const{
        if(rhs.Numerator() == 0){
            throw std::domain_error("Division by zero");
        }
        return {this->numerator * rhs.denominator, this->denominator * rhs.numerator};
    }

    bool operator==(const Rational& rhs) const{
        return this->numerator == rhs.numerator && this->denominator == rhs.denominator;
    }

    friend bool operator<(const Rational& lhs, const Rational&rhr) {
        return(lhs.Numerator()*rhr.Denominator() < rhr.Numerator()*lhs.Denominator());
    }

    friend std::istream& operator>>(std::istream& stream, Rational& r) {
        int prev_numerator = r.numerator;
        int prev_denominator = r.denominator;
        stream >> r.numerator;
        stream.ignore(1);
        stream >> r.denominator;

        if(r.numerator != prev_numerator || r.denominator != prev_denominator) {
            auto new_r = Rational(r.numerator, r.denominator);
            r = new_r;
        }
        return stream;
    }

    friend std::ostream& operator<<(std::ostream& stream, const Rational& r) {
        stream << r.numerator << "/" << r.denominator;
        return stream;
    }

private:
    // Добавьте поля
    int numerator;
    int denominator;

    int gcd(int a, int b) {
        if (b == 0)
            return a;
        return gcd(b, a % b);
    }

    int lcm(int a, int b){
        int temp = gcd(a, b);
        return temp ? (a / temp * b) : 0;
    }

    void shorten_for_common(int& a_num, int& a_den) {
        int common_divider = gcd(a_num, a_den);

        if (common_divider != 1) {
            while (a_num % common_divider == 0 && a_den % common_divider == 0) {
                a_num /= common_divider;
                a_den /= common_divider;
            }
        }
    }
};

void test_rational() {
    {
        const Rational r(3, 10);
        const Rational r2(30, 100);
        AssertEqual(r.Numerator(), r2.Numerator(), "not matched with given params");
        AssertEqual(r.Denominator(), r2.Denominator(), "denominators didn't match");
    }

    {
        const Rational r(2, 8);
        AssertEqual(r.Numerator(), 1, "not shortening");
        AssertEqual(r.Denominator(), 4, "denominator not shortening");
    }

    {
        Rational r;
        AssertEqual(r.Numerator(), 0, "default numerator not zero");
        AssertEqual(r.Denominator(), 1, "default denominator not one");
    }

    {
        const Rational r(1, -4);
        AssertEqual(r.Numerator(), -1, "negative value is not in numerator");
        AssertEqual(r.Denominator(), 4, "denominator left with negative value");
    }

    {
        const Rational r(-2, -3);
        AssertEqual(r.Numerator(), 2, "numerator negative value not terminated");
        AssertEqual(r.Denominator(), 3, "denominator negative value not terminated");
    }

    {
        const Rational r(-2, -4);
        AssertEqual(r.Numerator(), 1, "numerator negative values wasn't shortened");
        AssertEqual(r.Denominator(), 2, "denominator negative value wasn't shortened");
    }

    {
        const Rational r(0, -1);
        AssertEqual(r.Numerator(), 0, "zero numerator shouldn't have sign");
        AssertEqual(r.Denominator(), 1, "denominator negative value should be lifted to numerator");
    }
}


#endif //YELLOW_BELT_CPP_TEST_RATIONAL_H
