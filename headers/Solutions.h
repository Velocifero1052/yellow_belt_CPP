//
// Created by Legion on 4/26/2023.
//

#ifndef YELLOW_BELT_CPP_SOLUTIONS_H
#define YELLOW_BELT_CPP_SOLUTIONS_H

#include <iostream>
#include <vector>
#include <numeric>
#include <map>
#include <set>
#include <algorithm>

void average_temp_2(){
    size_t size_of_vector;
    std::cin >> size_of_vector;

    std::vector<int64_t> temps(size_of_vector);

    for(auto& elem: temps){
        std::cin >> elem;
    }

    int64_t average = std::accumulate(temps.begin(), temps.end(),
                                 decltype(temps)::value_type(0));
    average /= static_cast<int64_t>(temps.size());

    std::vector<size_t> res;
    for(size_t i = 0; i < temps.size(); i++){
        if(temps[i] > average)
            res.push_back(i);
    }

    std::cout << res.size() << '\n';
    bool first = true;
    for(const auto& elem: res){
        if (first) {
            std::cout << elem;
            first = false;
        }else{
            std::cout << " " << elem;
        }
    }
}

void canisters(){
    uint64_t n, r;
    uint64_t res = 0, w, h, d;
    std::cin >> n >> r;

    for(uint64_t i = 0; i < n; i++){
        std::cin >> w >> h >> d;
        res += w * h * d * r;
    }
    std::cout << res << '\n';
}

int minSubArrayLen(int target, const std::vector<int>& nums) {
    int i = 0, total = 0;
    int res = nums.size() + 1;
    for (int j = 0; j < nums.size(); j++) {
        total += nums[j];
        while (total >= target) {
            res = std::min(j - i + 1, res);
            total -= nums[i];
            i++;
        }
    }

    return res == nums.size() + 1 ? 0 : res;
}

int maxProfit(std::vector<int>& prices) {
    int i = 0, j = 1;
    int max_profit = 0;
    while (j < prices.size()) {
        if (prices[i] < prices[j]) {
            int profit = prices[j] - prices[i];
            max_profit = std::max(max_profit, profit);
        } else {
            i = j;
        }
        j++;
    }
    return max_profit;
}

template<typename K, typename V>
V& GetRefStrict(std::map<K, V>& m, K k);

template<typename K, typename V>
V& GetRefStrict(std::map<K, V>& m, K k){
    if(m.count(k) == 0)
        throw std::runtime_error("");
    return m.at(k);
}

void print_v(const std::vector<size_t>& v) {
    bool first = true;
    for(const auto& elem: v) {
        if (!first)
            std::cout << " ";
        first = false;
        std::cout << elem;
    }
    std::cout << '\n';
}

void reverse_permutation_task() {
    size_t size_of_vector;
    std::cin >> size_of_vector;

    std::vector<size_t> v(size_of_vector);
    for(size_t i = 0; i < v.size(); i++) {
        v[i] = size_of_vector - i;
    }

    do {
        print_v(v);
    } while(std::prev_permutation(v.begin(), v.end()));
}

template<typename T>
void RemoveDuplicates(std::vector<T>& v) {
    std::sort(v.begin(), v.end());
    auto last = unique(v.begin(), v.end());
    v.erase(last, v.end());
}


std::vector<std::string> SplitIntoWords(const std::string& s){

    std::vector<std::string> results;
    auto search_res = s.begin();
    bool first = true;
    while (search_res != s.end()) {

        auto prev = first ? search_res : next(search_res);
        first = false;
        search_res = find_if(prev, s.end(), [](const char& c) -> bool {
            return c == ' ';
        });
        results.emplace_back(prev, search_res);
    }

    return results;
}

void PrintVectorPart(const std::vector<int>& numbers){
    auto first_negative = find_if(numbers.begin(), numbers.end(), [](int num) -> bool{
        return num < 0;
    });
    bool first = true;
    while(first_negative != numbers.begin()) {
        --first_negative;
        if (!first) {
            std::cout << " " << *first_negative;
        } else {
            first = false;
            std::cout << *first_negative;
        }
    }
}

template <typename T>
std::vector<T> FindGreaterElements(const std::set<T>& elements, const T& border) {
    auto border_it = find_if(elements.begin(), elements.end(), [border](const T& elem) -> bool {
        return elem > border;
    });
    return {border_it, elements.end()};
}

template <typename RandomIt>
void MergeSortForTwo(RandomIt range_begin, RandomIt range_end) {
    int dist = distance(range_begin, range_end);
    if (dist < 2)
        return;
    std::vector<typename RandomIt::value_type> v(range_begin, range_end);
    MergeSortForTwo(v.begin(), v.begin() + v.size() / 2);
    MergeSortForTwo(v.begin() + v.size() / 2, v.end());
    merge(v.begin(), v.begin() + v.size() / 2, v.begin() + v.size() / 2, v.end(), range_begin);
}

#endif //YELLOW_BELT_CPP_SOLUTIONS_H
