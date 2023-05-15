#include <iostream>
#include <numeric>
#include <map>
#include <tuple>
#include <algorithm>
#include <set>
#include <iomanip>
#include <vector>
//#include "headers/teamplate_outputs.h"

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

    int operator-(const Date& rhs) const {

        if (this->year == rhs.year && this->month == rhs.month) {
            return this->day - rhs.day + 1;
        } else if (this->year == rhs.year) {

            int start_number_of_days = number_of_days(rhs.year, rhs.month) - rhs.day;
            int end_number_of_days = this->day;
            int sum = start_number_of_days + end_number_of_days;

            for (int i = rhs.month + 1; i < this->month; i++) {
                sum += number_of_days(this->year, i);
            }
            return sum;
        } else {
            int sum = 0;
            bool first = true;
            for (int i = this->month; i <= 12; i++) {
                if (first) {
                    sum += number_of_days(this->year, i) - this->day;
                    first = false;
                } else {
                    sum += number_of_days(this->year,i);
                }
            }

            for (int i = 1; i < rhs.month; i++) {
                sum += number_of_days(rhs.year, i);
            }
            sum += rhs.number_of_days(rhs.year, rhs.month);

            for (int i = this->year + 1; i < rhs.year; i++) {
                sum += is_leap_year(i) ? 366 : 365;
            }

            return sum;
        }
    }

    bool operator==(const Date& rhs) const{
        return this->year == rhs.GetYear() && this->month == rhs.GetMonth() && this->day == rhs.GetDay();
    }

    bool operator<(const Date& rhs) const {
        return this->year < rhs.GetYear()
               || this->year == rhs.GetYear() && this->month < rhs.GetMonth()
               || this->year == rhs.GetYear() && this->month == rhs.GetMonth() && this->day < rhs.GetDay();
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

int main() {

    /*int command_count;
    cin >> command_count;
    set<Date> periods;
    map<Date, long> period_to_income;

    for (int i = 0; i < command_count; i++) {
        string command;
        cin >> command;
        Date start, end;
        if (command == "Earn") {
            long income;
            cin >> start >> end >> income;
            periods.insert(start);
            periods.insert(end);
            period_to_income[start] = income;
            period_to_income[end] = income;
        } else if (command == "ComputeIncome") {
            cin >> start >> end;
            auto start_it = find_if(periods.begin(), periods.end(), [start](const Date& entry) -> bool {
                return start < entry;
            });
            auto end_it = find_if(periods.rbegin(), periods.rend(), [end](const Date& entry) -> bool {
                return entry < end;
            });
            if (start_it != periods.end())
                cout << *start_it << endl;
            if (end_it != periods.rend())
                cout << *end_it << endl;


            cout << start << " " << end << endl;

        }
    }*/
    {
        Date one(2000, 01, 01);
        Date two(2000, 01, 30);
        cout << "Same year and same month" << endl;
        cout << two - one << endl;
    }

    {
        Date one(2000, 01, 15);
        Date two(2000, 02, 6);
        cout << "Same year, next month" << endl;
        cout << two - one << '\n';
    }

    {
        Date one(2000, 01, 15);
        Date two(2000, 03, 6);
        cout << "Same year, two month difference" << endl;
        cout << two - one << '\n';
    }

    {
        Date one(2000, 01, 15);
        Date two(2000, 12, 6);
        cout << "Same year, next month" << endl;
        cout << two - one << '\n';
    }


    return 0;
}


