//
// Created by Legion on 5/2/2023.
//

#ifndef YELLOW_BELT_CPP_TEAMPLATE_OUTPUTS_H
#define YELLOW_BELT_CPP_TEAMPLATE_OUTPUTS_H

#include <ostream>
#include <utility>
#include <vector>
#include <map>
#include <string>
#include <sstream>

template <typename First, typename Second>
std::ostream& operator << (std::ostream& out, const std::pair<First, Second>& p);

template <typename T>
std::ostream& operator << (std::ostream& out, const std::vector<T>& vi);

template <typename Key, typename Value>
std::ostream& operator << (std::ostream& out, const std::map<Key, Value>& m);

template <typename Collection>
std::string Join(const Collection& c, char d) {
    std::stringstream ss;
    bool first = true;
    for (const auto& i : c) {
        if (!first) {
            ss << d;
        }
        first = false;
        ss << i;
    }
    return ss.str();
}

template <typename First, typename Second>
std::ostream& operator << (std::ostream& out, const std::pair<First, Second>& p) {
    return out << '(' << p.first << ',' << p.second << ')';
}

template <typename T>
std::ostream& operator << (std::ostream& out, const std::vector<T>& vi) {
    return out << '[' << Join(vi, ',') << ']';
}

template <typename Key, typename Value>
std::ostream& operator << (std::ostream& out, const std::map<Key, Value>& m) {
    return out << '{' << Join(m, ',') << '}';
}


#endif //YELLOW_BELT_CPP_TEAMPLATE_OUTPUTS_H
