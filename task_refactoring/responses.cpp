//
// Created by Rakhmon Radjabov on 11/05/23.
//
#include "responses.h"

std::ostream& operator << (std::ostream& os, const BusesForStopResponse& r) {
    if (r.buses_for_stop.empty()) {
        os << "No stop";
        return os;
    }
    bool first = true;

    for(const std::string& bus_for_stop: r.buses_for_stop) {
        if (!first) {
            os << " " << bus_for_stop;
        } else {
            os << bus_for_stop;
            first = false;
        }
    }

    return os;
}

std::ostream& operator << (std::ostream& os, const StopsForBusResponse& r) {
    if (r.buses_to_stops.empty()) {
        os << "No bus";
        return os;
    }

    for (const std::string& stop : r.buses_to_stops) {
        os << "Stop " << stop << ": ";
        if (r.stops_to_buses.at(stop).size() == 1) {
            os << "no interchange";
        } else {
            for (const std::string& other_bus : r.stops_to_buses.at(stop)) {
                if (r.bus != other_bus) {
                    os << other_bus << " ";
                }
            }
        }
        os << std::endl;
    }
    return os;
}

std::ostream& operator << (std::ostream& os, const AllBusesResponse& r) {

    if (r.all_buses.empty()) {
        os << "No buses";
    } else {
        for (const auto& bus_item : r.all_buses) {
            os << "Bus " << bus_item.first << ": ";
            for (const std::string& stop : bus_item.second) {
                os << stop << " ";
            }
            os << std::endl;
        }
    }
    return os;
}