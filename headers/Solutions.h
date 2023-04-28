//
// Created by Legion on 4/26/2023.
//

#ifndef YELLOW_BELT_CPP_SOLUTIONS_H
#define YELLOW_BELT_CPP_SOLUTIONS_H
#include <iostream>
#include <vector>
#include <numeric>

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

#endif //YELLOW_BELT_CPP_SOLUTIONS_H
