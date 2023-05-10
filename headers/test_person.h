//
// Created by comme on 5/10/2023.
//

#ifndef YELLOW_BELT_CPP_TEST_PERSON_H
#define YELLOW_BELT_CPP_TEST_PERSON_H

#include <string>
#include <map>
#include <algorithm>
#include "test_framework.h"

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
    AssertEqual(p.GetFullName(1995), "Noname Radjabov", "name and surname was given");
}

#endif //YELLOW_BELT_CPP_TEST_PERSON_H
