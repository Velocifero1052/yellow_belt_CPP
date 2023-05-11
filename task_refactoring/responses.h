//
// Created by Rakhmon Radjabov on 11/05/23.
//
#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <map>

struct BusesForStopResponse {
    std::vector<std::string> buses_for_stop;
};

std::ostream& operator << (std::ostream& os, const BusesForStopResponse& r);

struct StopsForBusResponse {
    std::vector<std::string> buses_to_stops;
    std::map<std::string, std::vector<std::string>> stops_to_buses;
    std::string bus;
};

std::ostream& operator << (std::ostream& os, const StopsForBusResponse& r);

struct AllBusesResponse {
    std::map<std::string, std::vector<std::string>> all_buses;
};

std::ostream& operator << (std::ostream& os, const AllBusesResponse& r);