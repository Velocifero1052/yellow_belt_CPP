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
    Date();

    Date(int year, int month, int day);

    int GetYear() const;

    int& GetYear();

    int GetMonth() const;

    int& GetMonth();

    int GetDay() const;

    int& GetDay();

    bool operator==(const Date& rhs) const;

    bool operator<(const Date& rhs) const;

    bool operator<=(const Date& rhs) const;

private:
    int year;
    int month;
    int day;
};

std::ostream& operator<<(std::ostream& stream, const Date& date);

std::istream& operator>>(std::istream& stream, Date& date);

int jdn_value(Date d);

#endif //YELLOW_BELT_CPP_DATE_H
