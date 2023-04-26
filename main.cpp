#include <iostream>
#include <vector>
#include <numeric>

using std::vector;
using std::cout;
using std::cin;
using std::out_of_range;
using std::invalid_argument;
using std::ostream;
using std::istream;
using std::accumulate;

int main() {

    size_t size_of_vector;
    cin >> size_of_vector;

    vector<int64_t> temps(size_of_vector);

    for(auto& elem: temps){
        cin >> elem;
    }

    int64_t average = accumulate(temps.begin(), temps.end(),
                                      decltype(temps)::value_type(0));
    average /= static_cast<int64_t>(temps.size());

    vector<size_t> res;
    for(size_t i = 0; i < temps.size(); i++){
        if(temps[i] > average)
            res.push_back(i);
    }

    cout << res.size() << '\n';
    bool first = true;
    for(const auto& elem: res){
        if (first) {
            cout << elem;
            first = false;
        }else{
            cout << " " << elem;
        }
    }

    return 0;
}
