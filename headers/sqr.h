//
// Created by Legion on 5/2/2023.
//

#ifndef YELLOW_BELT_CPP_SQR_H
#define YELLOW_BELT_CPP_SQR_H
#include <vector>
#include <map>
#include <utility>

template<typename T>
std::vector<T> Sqr(std::vector<T> v);

template<typename key, typename value>
std::map<key, value> Sqr(std::map<key, value> m);

/*template<typename F, typename S>
pair<F, S> operator* (pair<F, S> lhs, pair<F, S> rhs);*/

template<typename F, typename S>
std::pair<F, S> Sqr(std::pair<F, S> p);

template<typename T>
T Sqr(T x);


template<typename T>
std::vector<T> Sqr(std::vector<T> v) {
    for(std::size_t i = 0; i < v.size(); i++){
        v[i] = Sqr(v[i]);
    }
    return v;
}

template<typename key, typename value>
std::map<key, value> Sqr(std::map<key, value> m){
    for(auto& [first, second] : m){
        second = Sqr(second);
    }
    return m;
}

/*template<typename F, typename S>
pair<F, S> operator* (pair<F, S> lhs, pair<F, S> rhs){
    return make_pair(lhs.first * rhs.first, lhs.second * rhs.second);
}*/

template<typename F, typename S>
std::pair<F, S> Sqr(std::pair<F, S> p){
    p.first = Sqr(p.first);
    p.second = Sqr(p.second);
    return p;
}

template<typename T>
T Sqr(T x){
    return x * x;
}

#endif //YELLOW_BELT_CPP_SQR_H
