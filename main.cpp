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
    // Вы можете вставлять сюда различные реализации функции,
    // чтобы проверить, что ваши тесты пропускают корректный код
    // и ловят некорректный
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





int main() {
    TestRunner runner;
    runner.RunTest(test_roots_count, "all tests");


    return 0;
}


