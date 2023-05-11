#include "bus_manager.h"

void BusManager::AddBus(const std::string& bus, const std::vector<std::string>& stops_) {
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

BusesForStopResponse BusManager::GetBusesForStop(const std::string& stop) const {
    if (stops_to_buses.count(stop) == 0) {
        return BusesForStopResponse{{}};
    } else {
        return BusesForStopResponse{stops_to_buses.at(stop)};
    }
}

StopsForBusResponse BusManager::GetStopsForBus(const std::string& bus) const {
    if (buses_to_stops.count(bus) == 0) {
        return StopsForBusResponse{{}, {}, bus};
    } else {
        return StopsForBusResponse{buses_to_stops.at(bus), stops_to_buses, bus};
    }
}

AllBusesResponse BusManager::GetAllBuses() const{
    return AllBusesResponse{buses_to_stops};
}