//
// Created by Rakhmon Radjabov on 11/05/23.
//
#include "query.h"

std::istream& operator >> (std::istream& is, Query& q) {
    std::string command;
    is >> command;
    if (command == "NEW_BUS") {
        q.type = QueryType::NewBus;
        std::string bus;
        is >> bus;
        int stop_count;
        is >> stop_count;
        std::vector<std::string> stops;
        for (int i = 0; i < stop_count; i++) {
            std::string stop;
            is >> stop;
            stops.push_back(stop);
        }
        q.bus = bus;
        q.stops = stops;
    } else if (command == "BUSES_FOR_STOP") {
        q.type = QueryType::BusesForStop;
        std::string stop;
        is >> stop;
        q.stop = stop;
    } else if (command == "STOPS_FOR_BUS") {
        q.type = QueryType::StopsForBus;
        std::string bus;
        is >> bus;
        q.bus = bus;
    } else if (command == "ALL_BUSES") {
        q.type = QueryType::AllBuses;
    }

    return is;
}