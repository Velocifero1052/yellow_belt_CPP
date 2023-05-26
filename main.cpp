#include <iostream>
#include <numeric>
#include <vector>
#include <algorithm>
#include <deque>
//#include "headers/teamplate_outputs.h"

using namespace std;

int main() {

    int a;
    int number_of_commands;
    cin >> a;
    cin >> number_of_commands;
    deque<string> d;
    d.push_back(to_string(a));
    string operation;
    int value;

    for (int i = 0; i < number_of_commands; i++) {
        cin >> operation >> value;
        d.emplace_front("(");
        d.emplace_back(")");
        d.emplace_back(" ");
        d.push_back(operation);
        d.emplace_back(" ");
        d.push_back(to_string(value));
    }

    for(const string& str: d) {
        cout << str;
    }

    return 0;
}