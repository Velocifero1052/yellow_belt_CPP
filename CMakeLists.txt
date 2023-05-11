cmake_minimum_required(VERSION 3.25)
project(yellow_belt_CPP)

set(CMAKE_CXX_STANDARD 17)

add_executable(yellow_belt_CPP main.cpp headers/Matrix.h headers/Solutions.h headers/TaskTracker.h headers/teamplate_outputs.h headers/sqr.h headers/bus_stops.h headers/test_framework.h headers/distinct_root_number.h headers/test_person.h headers/test_rational.h headers/test_is_palindom.h headers/sum_reverse_sort.h definition/sum_reverse_sort.cpp)
