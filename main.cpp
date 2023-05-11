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

int main() {

/*    PrintVectorPart({6, 1, 8, -5, 4});
    cout << endl;
    PrintVectorPart({-6, 1, 8, -5, 4});  // ничего не выведется
    cout << endl;
    PrintVectorPart({6, 1, 8, 5, 4});
    cout << endl;*/

    return 0;
}


