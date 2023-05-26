#include <iostream>
#include <numeric>
#include <vector>
#include <algorithm>
//#include "headers/teamplate_outputs.h"

using namespace std;

template <typename RandomIt>
pair<RandomIt, RandomIt> FindStartsWith(
        RandomIt range_begin, RandomIt range_end,
        const string& prefix){
    if (range_begin == range_end) {
        return make_pair(range_end, range_end);
    }

    string s{prefix};

    auto start = lower_bound(range_begin, range_end, s);
   // prefix++;
    string s2{prefix};
    auto end = lower_bound(range_begin, range_end, s2);

    return make_pair(start, end);
}

int main() {

    const vector<string> sorted_strings = {"moscow", "murmansk", "vologda"};

  /*  const auto m_result =
            FindStartsWith(begin(sorted_strings), end(sorted_strings), 'm');
    for (auto it = m_result.first; it != m_result.second; ++it) {
        cout << *it << " ";
    }
    cout << endl;

    const auto p_result =
            FindStartsWith(begin(sorted_strings), end(sorted_strings), 'p');
    cout << (p_result.first - begin(sorted_strings)) << " " <<
         (p_result.second - begin(sorted_strings)) << endl;

    const auto z_result =
            FindStartsWith(begin(sorted_strings), end(sorted_strings), 'z');
    cout << (z_result.first - begin(sorted_strings)) << " " <<
         (z_result.second - begin(sorted_strings)) << endl;
*/
    return 0;
}