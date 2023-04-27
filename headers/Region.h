//
// Created by Legion on 4/27/2023.
//

#ifndef YELLOW_BELT_CPP_REGION_H
#define YELLOW_BELT_CPP_REGION_H

#include <set>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

enum class Lang {
    DE, FR, IT
};

struct Region {
    std::string std_name;
    std::string parent_std_name;
    std::map<Lang, std::string> names;
    int64_t population;
};

bool operator<(const Region& lhs, const Region& rhs) {
    return tie(lhs.std_name, lhs.parent_std_name, lhs.names, lhs.population) <
           tie(rhs.std_name, rhs.parent_std_name, rhs.names, rhs.population);
}

bool operator==(const Region& lhs, const Region& rhs){
    return tie(lhs.std_name, lhs.parent_std_name, lhs.names, lhs.population) ==
           tie(rhs.std_name, rhs.parent_std_name, rhs.names, rhs.population);
}

int FindMaxRepetitionCount(const std::vector<Region>& regions){
    std::set<Region> unique_regions(regions.begin(), regions.end());
    size_t max_repetitions = 0;
    for(const auto& entry: unique_regions){
        size_t curr_count = count_if(regions.begin(), regions.end(), [entry](const auto& region) -> bool {
            return region == entry;
        });
        if(curr_count > max_repetitions){
            max_repetitions = curr_count;
        }
    }

    return (int)max_repetitions;
}


#endif //YELLOW_BELT_CPP_REGION_H
