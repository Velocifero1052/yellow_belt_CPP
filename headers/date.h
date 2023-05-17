//
// Created by Rakhmon Radjabov on 17/05/23.
//

#ifndef YELLOW_BELT_CPP_DATE_H
#define YELLOW_BELT_CPP_DATE_H

#include <string>
#include <iomanip>
#include <sstream>

class Date {
public:

    Date(){
        year = 0;
        month = 0;
        day = 0;
    }

    Date(int year, int month, int day){
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

    int GetYear() const{
        return year;
    }

    int GetMonth() const{
        return month;
    }

    int GetDay() const{
        return day;
    }

    bool operator==(const Date& rhs) const{
        return this->year == rhs.GetYear() && this->month == rhs.GetMonth() && this->day == rhs.GetDay();
    }

    bool operator<(const Date& rhs) const {
        return this->year < rhs.GetYear()
               || this->year == rhs.GetYear() && this->month < rhs.GetMonth()
               || this->year == rhs.GetYear() && this->month == rhs.GetMonth() && this->day < rhs.GetDay();
    }

    bool operator<=(const Date& rhs) const {
        return *this < rhs || *this == rhs;
    }

    friend std::ostream& operator<<(std::ostream& stream, const Date& date) {
        stream << std::setw(4) << std::setfill('0') << date.GetYear() << "-"
            << std::setw(2) << std::setfill('0') << date.GetMonth() << "-"
            << std::setw(2) << std::setfill('0') << date.GetDay();
        return stream;
    }

    friend std::istream& operator>>(std::istream& stream, Date& date) {

        std::string string_buffer;
        stream >> string_buffer;
        std::stringstream ss(string_buffer);

        ss >> date.year;
        if ((char)ss.peek() != '-')
            throw std::domain_error("Wrong date format: " + string_buffer);
        ss.ignore(1);
        if(ss.eof()){
            throw std::domain_error("Wrong date format: " + string_buffer);
        }
        ss >> date.month;

        if ((char)ss.peek() != '-')
            throw std::domain_error("Wrong date format: " + string_buffer);

        ss.ignore(1);

        if(string_buffer.find('-', string_buffer.length() - 1) == string_buffer.length() - 1){
            throw std::domain_error("Wrong date format: " + string_buffer);
        }

        ss >> date.day;

        if(!ss.eof())
            throw std::domain_error("Wrong date format: " + string_buffer);

        auto new_date = Date(date.year, date.month, date.day);
        date = new_date;

        return stream;
    }

    bool is_leap_year(int year) const {
        return year % 400 == 0 || (year % 4 == 0 && year % 100 != 0);
    }

    int number_of_days(int year, int month) const {
        if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12)
            return 31;
        else if (month == 4 || month == 6 || month == 9 || month == 11) {
            return 30;
        } else {
            if (is_leap_year(year))
                return 29;
            else return 28;
        }
    }

private:
    int year;
    int month;
    int day;
};

int jdn_value(Date d) {
    return 367 * d.GetYear() - (7 * (d.GetYear() + 5001 + (d.GetMonth() - 9) / 7)) / 4 +
           (275 * d.GetMonth()) / 9 + d.GetDay() + 1729777;
}

#endif //YELLOW_BELT_CPP_DATE_H
