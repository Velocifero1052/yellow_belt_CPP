//
// Created by Rakhmon Radjabov on 11/05/23.
//

#include "../headers/phone_number.h"
#include <sstream>
#include <algorithm>

PhoneNumber::PhoneNumber(const std::string &international_number) {
    stringstream ss(international_number);
    if(ss.peek() != '+')
        throw invalid_argument("number must start with '+' sign");
    ss.ignore(1);
    string number;
    ss >> number;

    auto first_sign = find(number.begin(), number.end(), '-');
    if(first_sign == number.end())
        throw invalid_argument("number must contain '-' sign");

    auto second_sign = find(next(first_sign), number.end(), '-');

    if (second_sign == number.end())
        throw invalid_argument("number must contain second '-' sign");

    string international_code(number.begin(), first_sign);
    string city_code(next(first_sign), second_sign);
    string local_number(next(second_sign), number.end());

    if (international_code.empty())
        throw invalid_argument("international code is empty");

    if (city_code.empty())
        throw invalid_argument("city code is empty");

    if (local_number.empty())
        throw invalid_argument("local number is empty");

    this->country_code_ = international_code;
    this->city_code_ = city_code;
    this->local_number_ = local_number;
}

string PhoneNumber::GetCountryCode() const {
    return this->country_code_;
}

string PhoneNumber::GetCityCode() const {
    return this->city_code_;
}

string PhoneNumber::GetLocalNumber() const {
    return this->local_number_;
}

string PhoneNumber::GetInternationalNumber() const {
    return "+" + this->GetCountryCode() + "-" + this->GetCityCode() + "-" + this->GetLocalNumber();
}