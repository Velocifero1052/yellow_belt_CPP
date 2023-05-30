//
// Created by Rakhmon Radjabov on 30/05/23.
//

#ifndef YELLOW_BELT_CPP_DATABASE_H
#define YELLOW_BELT_CPP_DATABASE_H
#include "date.h"
#include <string>
#include <set>
#include <iostream>
#include <map>

using std::string;
using std::set;
using std::cout;
using std::map;

class Database {
public:
    void AddEvent(const Date& date, const string& event);

    bool DeleteEvent(const Date& date, const string& event);

    int DeleteDate(const Date& date);

    int Find(const Date& date) const;

    void Print() const;

    set<string>& getEvents(Date& date);

private:
    map<Date, set<string>> db;
};

#endif //YELLOW_BELT_CPP_DATABASE_H
