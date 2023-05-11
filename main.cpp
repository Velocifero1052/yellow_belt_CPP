#include <iostream>
#include <vector>
#include <numeric>
#include <map>
#include <tuple>
#include <algorithm>
#include <set>
#include <sstream>

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

int main() {
    string s = "Cpp Java Python C";

    vector<string> words = SplitIntoWords(s);
    cout << words.size() << " ";
    for (auto it = begin(words); it != end(words); ++it) {
        if (it != begin(words)) {
            cout << "/";
        }
        cout << *it;
    }
    cout << endl;

    return 0;
}


