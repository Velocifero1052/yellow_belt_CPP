//
// Created by Rakhmon Radjabov on 25/05/23.
//

#ifndef YELLOW_BELT_CPP_PERSONFOUR_H
#define YELLOW_BELT_CPP_PERSONFOUR_H

#include <string>
#include <map>
#include <iostream>

class Person {
public:
    void ChangeFirstName(int year, const std::string& first_name) {
        years_to_names[year] = first_name;
    }
    void ChangeLastName(int year, const std::string& last_name) {
        years_to_lastnames[year] = last_name;
    }
    std::string GetFullName(int year) {
        std::string firstname = search_data(year, years_to_names, UNKNOWN_FIRST_NAME);
        std::string lastname = search_data(year, years_to_lastnames, UNKNOWN_LAST_NAME);

        if (firstname == UNKNOWN_FIRST_NAME && lastname == UNKNOWN_LAST_NAME)
            return UNKNOWN_PERSON_VALUE;
        else if (lastname == UNKNOWN_LAST_NAME)
            return firstname + " with " + lastname;
        else if (firstname == UNKNOWN_FIRST_NAME)
            return lastname + " with " + firstname;
        else return firstname + " " + lastname;
    }
private:
    std::string search_data(int year, const std::map<int, std::string>& m, const std::string& default_value) {
        std::string res;
        auto search_res = m.lower_bound(year);
        if (search_res == m.begin()) {
            if (year == search_res->first) {
                res = search_res->second;
            } else {
                res = default_value;
            }
        } else if (search_res == m.end()) {
            if (m.empty()) {
                res = default_value;
            } else {
                res = prev(search_res)->second;
            }
        } else {
            if (search_res->first == year) {
                res = search_res->second;
            } else {
                res = prev(search_res)->second;
            }
        }
        return res;
    }
    std::map<int, std::string> years_to_names;
    std::map<int, std::string> years_to_lastnames;
    const std::string UNKNOWN_PERSON_VALUE = "Incognito";
    const std::string UNKNOWN_LAST_NAME = "unknown last name";
    const std::string UNKNOWN_FIRST_NAME = "unknown first name";
};

void person_sample() {
    Person person;
    person.ChangeFirstName(1965, "Polina");
    person.ChangeLastName(1967, "Sergeeva");
    for (int year : {1900, 1965, 1990}) {
        std::cout << person.GetFullName(year) << std::endl;
    }

    person.ChangeFirstName(1970, "Appolinaria");
    for (int year : {1969, 1970}) {
        std::cout << person.GetFullName(year) << std::endl;
    }

    person.ChangeLastName(1968, "Volkova");
    for (int year : {1969, 1970}) {
        std::cout << person.GetFullName(year) << std::endl;
    }

}

#endif //YELLOW_BELT_CPP_PERSONFOUR_H
