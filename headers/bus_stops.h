//
// Created by Rakhmon Radjabov on 10/05/23.
//

#ifndef YELLOW_BELT_CPP_BUS_STOPS_H
#define YELLOW_BELT_CPP_BUS_STOPS_H

#include <string>
#include <map>
#include <vector>
#include <iostream>

enum class QueryType {
    NewBus,
    BusesForStop,
    StopsForBus,
    AllBuses
};

struct Query {
    QueryType type;
    std::string bus;
    std::string stop;
    std::vector<std::string> stops;
};

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

struct BusesForStopResponse {
    std::vector<std::string> buses_for_stop;
};

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

struct StopsForBusResponse {
    std::vector<std::string> buses_to_stops;
    std::map<std::string, std::vector<std::string>> stops_to_buses;
    std::string bus;
};

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

struct AllBusesResponse {
    std::map<std::string, std::vector<std::string>> all_buses;
};

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

class BusManager {
public:
    void AddBus(const std::string& bus, const std::vector<std::string>& stops_) {
        for(const std::string& stop: stops_) {
            if (stops_to_buses.count(stop) == 0) {
                stops_to_buses[stop] = {};
            }
            if (buses_to_stops.count(bus) == 0) {
                buses_to_stops[bus] = {};
            }
            stops_to_buses[stop].push_back(bus);
            buses_to_stops[bus].push_back(stop);
        }
    }

    BusesForStopResponse GetBusesForStop(const std::string& stop) const {
        if (stops_to_buses.count(stop) == 0) {
            return BusesForStopResponse{{}};
        } else {
            return BusesForStopResponse{stops_to_buses.at(stop)};
        }
    }

    StopsForBusResponse GetStopsForBus(const std::string& bus) const {
        if (buses_to_stops.count(bus) == 0) {
            return StopsForBusResponse{{}, {}, bus};
        } else {
            return StopsForBusResponse{buses_to_stops.at(bus), stops_to_buses, bus};
        }
    }

    AllBusesResponse GetAllBuses() const {
        return AllBusesResponse{buses_to_stops};
    }
private:
    std::map<std::string, std::vector<std::string>> buses_to_stops;
    std::map<std::string, std::vector<std::string>> stops_to_buses;
};

void test() {
    int query_count;
    Query q;
    std::cin >> query_count;
    BusManager bm;
    for (int i = 0; i < query_count; ++i) {
        std::cin >> q;
        switch (q.type) {
            case QueryType::NewBus:
                bm.AddBus(q.bus, q.stops);
                break;
            case QueryType::BusesForStop:
                std::cout << bm.GetBusesForStop(q.stop) << std::endl;
                break;
            case QueryType::StopsForBus:
                std::cout << bm.GetStopsForBus(q.bus) << std::endl;
                break;
            case QueryType::AllBuses:
                std::cout << bm.GetAllBuses() << std::endl;
                break;
        }
    }
}

#endif //YELLOW_BELT_CPP_BUS_STOPS_H
