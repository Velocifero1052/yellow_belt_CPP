//
// Created by Rakhmon Radjabov on 17/05/23.
//

#ifndef YELLOW_BELT_CPP_PERSONAL_BUDJET_H
#define YELLOW_BELT_CPP_PERSONAL_BUDJET_H

#include "date.h"
#include <vector>
#include <iostream>
#include <string>
#include <numeric>

void personal_budget_starter() {
    int to_sub = jdn_value(Date(2000, 01, 01));
    std::vector<double> days(36525, 0);

    int command_count;
    std::cin >> command_count;

    for (int command_number = 0; command_number < command_count; command_number++) {
        std::string command;
        std::cin >> command;
        Date start, end;
        if (command == "Earn") {
            double income;
            std::cin >> start >> end >> income;
            int i, j;
            if (start <= end) {
                i = jdn_value(start) - to_sub;
                j = jdn_value(end) - to_sub;
            } else {
                i = jdn_value(end) - to_sub;
                j = jdn_value(start) - to_sub;
            }

            int number_of_days = j - i + 1;

            double value = (double)income / number_of_days;
            for (; i <= j; i++) {
                days[i] += value;
            }

        } else if (command == "ComputeIncome") {
            std::cin >> start >> end;
            int i, j;

            if (start <= end) {
                i = jdn_value(start) - to_sub;
                j = jdn_value(end) - to_sub;
            } else {
                i = jdn_value(end) - to_sub;
                j = jdn_value(start) - to_sub;
            }
            double starter = 0.0;
            double sum  = std::accumulate(days.begin() + i, days.begin() + j + 1, starter);
            std::cout.precision(25);
            std::cout << sum << '\n';
        }
    }
}


#endif //YELLOW_BELT_CPP_PERSONAL_BUDJET_H
