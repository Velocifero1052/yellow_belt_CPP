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


#endif //YELLOW_BELT_CPP_SOLUTIONS_H
