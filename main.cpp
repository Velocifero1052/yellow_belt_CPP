#include <iostream>
#include <numeric>
#include <iomanip>
#include <vector>
#include <sstream>
#include <set>
#include <map>
#include <algorithm>
//#include "headers/test_framework.h"

using namespace std;

template <typename RandomIt>
pair<RandomIt, RandomIt> FindStartsWith(RandomIt range_begin, RandomIt range_end, char prefix) {
    return make_pair(range_begin, range_end);
}

int main() {

    const vector<string> sorted_strings = {"moscow", "murmansk", "vologda"};

    const auto m_result =
            FindStartsWith(begin(sorted_strings), end(sorted_strings), 'm');
    for (auto it = m_result.first; it != m_result.second; ++it) {
        cout << *it << " ";
    }

    auto it = lower_bound(sorted_strings.begin(), sorted_strings.end(), "m");
    cout << "################################################################" << endl;
    cout << *it << endl;
    cout << "################################################################" << endl;

    cout << endl;

    return 0;
}


