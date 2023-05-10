#include <iostream>
#include <vector>
#include <numeric>
#include <map>
#include <tuple>
#include <algorithm>
#include <set>
#include "headers/test_framework.h"

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

int GetDistinctRealRootCount(double a, double b, double c) {
    if(a != 0.0 && b != 0.0) {
        double under_root_expression = b * b - 4 * a * c;
        if (under_root_expression < 0.0) {
            return 0;
        } else if (under_root_expression == 0.0) {
            return 1;
        } else {
            return 2;
        }
    }else if(a == 0.0 && b != 0.0 && c != 0.0){
        return 1;
    }else if(a != 0.0 && c == 0.0 || a == 0.0 && b != 0.0){
        return 1;
    }else if(a != 0.0 && -c / a >= 0.0){
        return 2;
    }else{
        return 0;
    }
}

void test_roots_count(){
    AssertEqual(GetDistinctRealRootCount(2, 1, 2), 0, "negative under root expression");
    AssertEqual(GetDistinctRealRootCount(2,4,2), 1, "zero under root expression has one root");
    AssertEqual(GetDistinctRealRootCount(1, 4, 1), 2, "normal square equation");
    AssertEqual(GetDistinctRealRootCount(1, 0, 0), 1, "one variable only");
    AssertEqual(GetDistinctRealRootCount(0, 1, 0), 1, "linear equation");
    AssertEqual(GetDistinctRealRootCount(0.1, -1, 1), 2, "two roots");
    AssertEqual(GetDistinctRealRootCount(0, 0, 1), 0, "no variables no roots");
}

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
    AssertEqual(p.GetFullName(1995), "Rakhmon Radjabov", "name and surname was given");
}

int main() {

    TestRunner runner;
    runner.RunTest(test_roots_count, "all get root number tests");
    runner.RunTest(test_person_names, "person tests");

    return 0;
}


