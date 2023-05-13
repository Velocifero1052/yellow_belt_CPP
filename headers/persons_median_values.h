//
// Created by Rakhmon Radjabov on 12/05/23.
//

#ifndef YELLOW_BELT_CPP_PERSONS_MEDIAN_VALUES_H
#define YELLOW_BELT_CPP_PERSONS_MEDIAN_VALUES_H

#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

template <typename InputIt>
int ComputeMedianAge(InputIt range_begin, InputIt range_end);

enum class Gender {
    FEMALE,
    MALE
};

struct Person {
    int age;
    Gender gender;
    bool is_employed;
};

void PrintStats(std::vector<Person> persons) {
    int median_age = ComputeMedianAge(persons.begin(), persons.end());

    auto last = partition(persons.begin(), persons.end(), [](const Person& person)-> bool {
        return person.gender == Gender::FEMALE;
    });
    int median_female_age = ComputeMedianAge(persons.begin(), last);

    last = partition(persons.begin(), persons.end(), [](const Person& person)-> bool {
        return person.gender == Gender::MALE;
    });
    int median_male_age = ComputeMedianAge(persons.begin(), last);

    last = partition(persons.begin(), persons.end(), [](const Person& person)-> bool {
        return person.gender == Gender::FEMALE && person.is_employed;
    });
    int median_employed_female = ComputeMedianAge(persons.begin(), last);

    last = partition(persons.begin(), persons.end(), [](const Person& person)-> bool {
        return person.gender == Gender::FEMALE && !person.is_employed;
    });
    int median_unemployed_female = ComputeMedianAge(persons.begin(), last);

    last = partition(persons.begin(), persons.end(), [](const Person& person)-> bool {
        return person.gender == Gender::MALE && person.is_employed;
    });
    int median_employed_male = ComputeMedianAge(persons.begin(), last);

    last = partition(persons.begin(), persons.end(), [](const Person& person)-> bool {
        return person.gender == Gender::MALE && !person.is_employed;
    });
    int median_unemployed_male = ComputeMedianAge(persons.begin(), last);

    std::string median_age_message = "Median age";

    std::cout << median_age_message << " = " << median_age << '\n';
    std::cout << median_age_message << " for females = " << median_female_age << '\n';
    std::cout << median_age_message << " for males = " << median_male_age << '\n';
    std::cout << median_age_message << " for employed females = " << median_employed_female << '\n';
    std::cout << median_age_message << " for unemployed females = " << median_unemployed_female << '\n';
    std::cout << median_age_message << " for employed males = " << median_employed_male << '\n';
    std::cout << median_age_message << " for unemployed males = " << median_unemployed_male << '\n';

}

template <typename InputIt>
int ComputeMedianAge(InputIt range_begin, InputIt range_end) {
    if (range_begin == range_end) {
        return 0;
    }
    std::vector<typename InputIt::value_type> range_copy(range_begin, range_end);
    auto middle = begin(range_copy) + range_copy.size() / 2;
    nth_element(
            begin(range_copy), middle, end(range_copy),
            [](const Person& lhs, const Person& rhs) {
                return lhs.age < rhs.age;
            }
    );
    return middle->age;
}
void tests() {
    std::vector<Person> persons = {
            {31, Gender::MALE, false},
            {40, Gender::FEMALE, true},
            {24, Gender::MALE, true},
            {20, Gender::FEMALE, true},
            {80, Gender::FEMALE, false},
            {78, Gender::MALE, false},
            {10, Gender::FEMALE, false},
            {55, Gender::MALE, true},
    };
    PrintStats(persons);
}

#endif //YELLOW_BELT_CPP_PERSONS_MEDIAN_VALUES_H
