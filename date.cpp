//
// Created by Rakhmon Radjabov on 30/05/23.
//

#include "date.h"

Date::Date() {
    year = 0;
    month = 0;
    day = 0;
}

Date::Date(int year, int month, int day) {
    this->year = year;
    if(!(month >= 1 && month <= 12)) {
        std::string error_message = "Month value is invalid: " + std::to_string(month);
        throw std::invalid_argument(error_message);
    }
    this->month = month;
    if(!(day >= 1 && day <= 31)){
        std::string error_message = "Day value is invalid: " + std::to_string(day);
        throw std::invalid_argument(error_message);
    }
    this->day = day;
}

int Date::GetYear() const{
    return year;
}

int& Date::GetYear() {
    return year;
}

int Date::GetMonth() const {
    return month;
}

int& Date::GetMonth() {
    return month;
}

int Date::GetDay() const {
    return day;
}

int& Date::GetDay() {
    return day;
}

bool Date::operator==(const Date& rhs) const {
    return this->year == rhs.GetYear() && this->month == rhs.GetMonth() && this->day == rhs.GetDay();
}

bool Date::operator<(const Date& rhs) const {
    return this->year < rhs.GetYear()
           || this->year == rhs.GetYear() && this->month < rhs.GetMonth()
           || this->year == rhs.GetYear() && this->month == rhs.GetMonth() && this->day < rhs.GetDay();
}

bool Date::operator<=(const Date& rhs) const {
    return *this < rhs || *this == rhs;
}

std::ostream& operator<<(std::ostream& stream, const Date& date) {
    stream << std::setw(4) << std::setfill('0') << date.GetYear() << "-"
           << std::setw(2) << std::setfill('0') << date.GetMonth() << "-"
           << std::setw(2) << std::setfill('0') << date.GetDay();
    return stream;
}

std::istream& operator>>(std::istream& stream, Date& date) {

    std::string string_buffer;
    stream >> string_buffer;
    std::stringstream ss(string_buffer);

    ss >> date.GetYear();
    if ((char)ss.peek() != '-')
        throw std::domain_error("Wrong date format: " + string_buffer);
    ss.ignore(1);
    if(ss.eof()){
        throw std::domain_error("Wrong date format: " + string_buffer);
    }
    ss >> date.GetMonth();

    if ((char)ss.peek() != '-')
        throw std::domain_error("Wrong date format: " + string_buffer);

    ss.ignore(1);

    if(string_buffer.find('-', string_buffer.length() - 1) == string_buffer.length() - 1){
        throw std::domain_error("Wrong date format: " + string_buffer);
    }

    ss >> date.GetDay();

    if(!ss.eof())
        throw std::domain_error("Wrong date format: " + string_buffer);

    auto new_date = Date(date.GetYear(), date.GetMonth(), date.GetDay());
    date = new_date;

    return stream;
}

int jdn_value(Date d) {
    return 367 * d.GetYear() - (7 * (d.GetYear() + 5001 + (d.GetMonth() - 9) / 7)) / 4 +
           (275 * d.GetMonth()) / 9 + d.GetDay() + 1729777;
}