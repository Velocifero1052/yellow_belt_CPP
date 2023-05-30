//
// Created by Rakhmon Radjabov on 30/05/23.
//
#include "database.h"

void Database::AddEvent(const Date& date, const string& event){
    if(db.count(date) == 0)
        db[date] = set<string>();
    db[date].insert(event);
}

bool Database::DeleteEvent(const Date& date, const string& event){

    if(db.count(date) != 0){
        auto events = db[date];
        if(events.count(event) == 0)
            return false;
        else{
            events.erase(event);
            db[date] = events;
            return true;
        }
    }
    return false;
}

int Database::DeleteDate(const Date& date){
    if(db.count(date) == 0)
        return 0;
    size_t number_of_events = db[date].size();
    db.erase(date);
    return (int)number_of_events;
}

int Database::Find(const Date& date) const{
    return (int)db.count(date);
}

void Database::Print() const{
    for(const auto& [key, value]: db){
        for(const auto& event: value){
            cout << key << " " << event << '\n';
        }
    }
}

set<string>& Database::getEvents(Date& date){
    return db[date];
}