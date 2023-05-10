#include <iostream>
#include <vector>
#include <numeric>
#include <map>
#include <tuple>
#include <algorithm>
#include <set>
#include "headers/test_framework.h"

using std::vector;
using std::cout;
using std::cin;
using std::out_of_range;
using std::invalid_argument;
using std::ostream;
using std::istream;
using std::accumulate;
using std::stringstream;
using std::string;
using std::map;
using std::set;
using std::count_if;
using std::unique;
using std::tuple;
using std::min;
using std::find_if;
using std::endl;
using std::pair;
using std::make_pair;

int GetDistinctRealRootCount(double a, double b, double c) {
    if(a != 0.0 && b != 0.0) {
        double under_root_expression = b * b - 4 * a * c;
        if (under_root_expression < 0.0) {
            return 0;
        } else if (under_root_expression == 0.0) {
            return 1;
        } else {
            return 2;
        }
    }else if(a == 0.0 && b != 0.0 && c != 0.0){
        return 1;
    }else if(a != 0.0 && c == 0.0 || a == 0.0 && b != 0.0){
        return 1;
    }else if(a != 0.0 && -c / a >= 0.0){
        return 2;
    }else{
        return 0;
    }
}

void test_roots_count(){
    AssertEqual(GetDistinctRealRootCount(2, 1, 2), 0, "negative under root expression");
    AssertEqual(GetDistinctRealRootCount(2,4,2), 1, "zero under root expression has one root");
    AssertEqual(GetDistinctRealRootCount(1, 4, 1), 2, "normal square equation");
    AssertEqual(GetDistinctRealRootCount(1, 0, 0), 1, "one variable only");
    AssertEqual(GetDistinctRealRootCount(0, 1, 0), 1, "linear equation");
    AssertEqual(GetDistinctRealRootCount(0.1, -1, 1), 2, "two roots");
    AssertEqual(GetDistinctRealRootCount(0, 0, 1), 0, "no variables no roots");
}

class Person {
public:
    void ChangeFirstName(int year, const std::string& first_name) {
        years_to_names[year] = first_name;
    }
    void ChangeLastName(int year, const std::string& last_name) {
        years_to_lastnames[year] = last_name;
    }
    std::string GetFullName(int year) {

        auto name_search_res =  find_if(years_to_names.rbegin(), years_to_names.rend(),
                                        [year](const std::pair<int, std::string>& entry)-> bool {
                                                    return entry.first <= year;
                                                    });
        auto lastname_search_res =  find_if(years_to_lastnames.rbegin(), years_to_lastnames.rend(),
                                            [year](const std::pair<int, std::string>& entry)-> bool {
                                                    return entry.first <= year;
                                                    });
        bool name_found = name_search_res != years_to_names.rend();
        bool lastname_found = lastname_search_res != years_to_lastnames.rend();

        if(name_found && lastname_found){
            return name_search_res->second + " " + lastname_search_res->second;
        }else if(name_found){
            return name_search_res->second + " with unknown last name";
        }else if(lastname_found){
            return lastname_search_res->second + " with unknown first name";
        }else {
            return "Incognito";
        }
    }
private:
    std::map<int, std::string> years_to_names;
    std::map<int, std::string> years_to_lastnames;
};


void test_person_names(){
    Person p;
    AssertEqual(p.GetFullName(2023), "Incognito", "not initialized person must be incognito");
    p.ChangeFirstName(1993, "Rakhmon");
    AssertEqual(p.GetFullName(1995), "Rakhmon with unknown last name", "name was given, but not displayed");
    p.ChangeFirstName(1994, "Noname");
    AssertEqual(p.GetFullName(1995), "Noname with unknown last name", "new name was already given");
    p.ChangeLastName(1990, "Radjabov");
    AssertEqual(p.GetFullName(1991), "Radjabov with unknown first name", "last name was already given but not displayed");
    AssertEqual(p.GetFullName(1993), "Rakhmon Radjabov", "name and surname was given");
    AssertEqual(p.GetFullName(1995), "Rakhmon Radjabov", "name and surname was given");
}

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

    const Rational r(3, 10);
    const Rational r3(30, 100);

    AssertEqual(r.Numerator(),r3.Numerator(), "not matched with given params");
    Assert

}

int main() {

    TestRunner runner;
    runner.RunTest(test_roots_count, "all get root number tests");
    runner.RunTest(test_person_names, "person tests");

    return 0;
}


