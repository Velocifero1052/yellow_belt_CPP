#include <iostream>
#include <vector>
#include <numeric>
#include <map>
#include <tuple>
#include <algorithm>
#include <set>
#include <sstream>
#include "headers/sum_reverse_sort.h"
#include "headers/teamplate_outputs.h"
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



int main() {

    cout << Sum(2, 3) << endl;
    cout << Reverse("Madam") << endl;
    vector<int> v = {1, 5, 3, 4};
    Sort(v);
    cout << v << endl;

    return 0;
}


