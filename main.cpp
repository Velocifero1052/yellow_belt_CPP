#include <iostream>
#include <numeric>
#include <map>
#include <tuple>
#include <vector>
#include <algorithm>
#include "headers/teamplate_outputs.h"
#include <set>

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

using namespace std;

template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end) {
    int dist = distance(range_begin, range_end);
    if (dist < 2)
        return;
    std::vector<typename RandomIt::value_type> v(range_begin, range_end);
    MergeSort(v.begin(), v.begin() + v.size() / 2);
    MergeSort(v.begin() + v.size() / 2, v.end());
    merge(v.begin(), v.begin() + v.size() / 2, v.begin() + v.size() / 2, v.end(), range_begin);
}

int main() {
    vector<int> v = {6, 4, 7, 6, 4, 4, 0, 1};
    MergeSort(v.begin(), v.end());
    cout << v;
    return 0;
}


