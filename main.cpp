#include <iostream>
#include <numeric>
#include <map>
#include <tuple>
#include <algorithm>
#include <set>
#include <iomanip>
#include <vector>
#include <sstream>
//#include "headers/test_framework.h"

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
using std::cerr;
using std::ostringstream;
using std::runtime_error;
using std::exception;
using std::partition;
using std::to_string;
using std::setw;
using std::setfill;

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
            string error_message = "Month value is invalid: " + to_string(month);
            throw std::invalid_argument(error_message);
        }
        this->month = month;
        if(!(day >= 1 && day <= 31)){
            string error_message = "Day value is invalid: " + to_string(day);
            throw invalid_argument(error_message);
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
        stream << setw(4) << setfill('0') << date.GetYear() << "-" <<
               setw(2) << setfill('0') << date.GetMonth() << "-" <<
               setw(2) << setfill('0') << date.GetDay();
        return stream;
    }

    friend std::istream& operator>>(std::istream& stream, Date& date) {

        string string_buffer;
        stream >> string_buffer;
        stringstream ss(string_buffer);

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

/*void date_tests() {
    {
        Date one(2000, 01, 01);
        Date two(2000, 01, 30);
        AssertEqual(jdn_value(two) - jdn_value(one) + 1, 30, "one month difference is incorrect");
    }
    {
        Date one(2000, 01, 15);
        Date two(2000, 02, 6);
        AssertEqual(jdn_value(two) - jdn_value(one) + 1, 23, "same year next month");
    }
    {
        Date one(2000, 01, 15);
        Date two(2000, 03, 6);
        AssertEqual(jdn_value(two) - jdn_value(one) + 1, 52,"same year, two month difference");
    }
    {
        Date one(2000, 01, 15);
        Date two(2000, 12, 6);
        AssertEqual(jdn_value(two) - jdn_value(one) + 1, 327, "Same year last month");
    }
    {
        Date one(2000, 01, 01);
        Date two(2099, 12, 31);
        AssertEqual(jdn_value(two) - jdn_value(one) + 1, 36525, "One century difference");
    }
}*/

int main() {

    /*TestRunner tr;
    tr.RunTest(date_tests, "Date tests");*/

    int to_sub = jdn_value(Date(2000, 01, 01));
    vector<double> days(36525, 0);

    int command_count;
    cin >> command_count;

    for (int command_number = 0; command_number < command_count; command_number++) {
        string command;
        cin >> command;
        Date start, end;
        if (command == "Earn") {
            double income;
            cin >> start >> end >> income;
            int i, j;
            if (start <= end) {
                i = jdn_value(start) - to_sub;
                j = jdn_value(end) - to_sub;
            } else {
                i = jdn_value(end) - to_sub;
                j = jdn_value(start) - to_sub;
            }
            /*cout << "i: " << i << endl;
            cout << "j: " << j << endl;*/
            int number_of_days = j - i + 1;
            /*cout << "Number of days: " << number_of_days << endl;
            cout << "Number of JDN days: " << j - i << endl;*/
            double value = (double)income / number_of_days;
            for (; i <= j; i++) {
                days[i] += value;
            }
            /*cout.precision(25);*/
            /*cout << days[0] << endl;
            cout << days[days.size() - 1] << endl;*/

        } else if (command == "ComputeIncome") {
            cin >> start >> end;
            int i, j;

            if (start <= end) {
                i = jdn_value(start) - to_sub;
                j = jdn_value(end) - to_sub;
            } else {
                i = jdn_value(end) - to_sub;
                j = jdn_value(start) - to_sub;
            }
            double starter = 0.0;
            double sum  = std::accumulate(days.begin() + i, days.begin() + j + 1, starter);
            cout.precision(25);
            cout << sum << '\n';
        }
    }

    return 0;
}


