#include <iostream>
#include <vector>
#include <numeric>
#include <map>
#include <tuple>
#include <algorithm>
#include <set>
#include <sstream>
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

void PrintVectorPart(const vector<int>& numbers){
    auto first_negative = find_if(numbers.begin(), numbers.end(), [](int num) -> bool{
        return num < 0;
    });
    bool first = true;
    while(first_negative != numbers.begin()) {
        --first_negative;
        if (!first) {
            cout << " " << *first_negative;
        } else {
            first = false;
            cout << *first_negative;
        }
    }


}

template <typename T>
vector<T> FindGreaterElements(const set<T>& elements, const T& border) {
    auto border_it = find_if(elements.begin(), elements.end(), [border](const T& elem) -> bool {
        return elem > border;
    });
    return {border_it, elements.end()};
}

vector<string> SplitIntoWords(const string& s){

    vector<string> results;
    auto search_res = s.begin();
    bool first = true;
    while (search_res != s.end()) {

        auto prev = first ? search_res : next(search_res);
        first = false;
        search_res = find_if(prev, s.end(), [](const char& c) -> bool {
            return c == ' ';
        });
        results.emplace_back(prev, search_res);
    }

    return results;
}

enum class Gender {
    FEMALE,
    MALE
};

struct Person {
    int age;  // возраст
    Gender gender;  // пол
    bool is_employed;  // имеет ли работу
};

void PrintStats(vector<Person> persons) {

}

template <typename InputIt>
int ComputeMedianAge(InputIt range_begin, InputIt range_end) {
    if (range_begin == range_end) {
        return 0;
    }
    vector<typename InputIt::value_type> range_copy(range_begin, range_end);
    auto middle = begin(range_copy) + range_copy.size() / 2;
    nth_element(
            begin(range_copy), middle, end(range_copy),
            [](const Person& lhs, const Person& rhs) {
                return lhs.age < rhs.age;
            }
    );
    return middle->age;
}

int main() {

    return 0;
}


