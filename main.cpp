#include <iostream>
#include <vector>
#include <numeric>
#include <stdint.h>

using std::vector;
using std::cout;
using std::cin;
using std::out_of_range;
using std::invalid_argument;
using std::ostream;
using std::istream;
using std::accumulate;

int main() {

    uint64_t n, r;
    uint64_t res = 0, w, h, d;
    cin >> n >> r;

    for(uint64_t i = 0; i < n; i++){
        cin >> w >> h >> d;
        res += w * h * d * r;
    }
    cout << res << '\n';
    return 0;
}
