#include <iostream>
#include <vector>
#include <numeric>
#include <map>
#include <tuple>
#include <algorithm>
#include <set>

using std::vector;
using std::cout;
using std::cin;
using std::out_of_range;
using std::invalid_argument;
using std::ostream;
using std::istream;
using std::accumulate;
using std::stringstream;
using std::string;
using std::map;
using std::set;
using std::count_if;
using std::unique;
using std::tuple;
using std::min;
using std::find_if;
using std::endl;
using std::pair;
using std::make_pair;

enum class QueryType {
    NewBus,
    BusesForStop,
    StopsForBus,
    AllBuses
};

struct Query {
    QueryType type;
    string bus;
    string stop;
    vector<string> stops;
};

istream& operator >> (istream& is, Query& q) {
    string command;
    is >> command;
    if (command == "NEW_BUS") {
        q.type = QueryType::NewBus;
        string bus;
        is >> bus;
        int stop_count;
        is >> stop_count;
        vector<string> stops;
        for (int i = 0; i < stop_count; i++) {
            string stop;
            is >> stop;
            stops.push_back(stop);
        }
        q.bus = bus;
        q.stops = stops;
    } else if (command == "BUSES_FOR_STOP") {
        q.type = QueryType::BusesForStop;
        string stop;
        is >> stop;
        q.stop = stop;
    } else if (command == "STOPS_FOR_BUS") {
        q.type = QueryType::StopsForBus;
        string bus;
        is >> bus;
        q.bus = bus;
    } else if (command == "ALL_BUSES") {
        q.type = QueryType::AllBuses;
    }

    return is;
}

struct BusesForStopResponse {
    vector<string> buses_for_stop;
};

ostream& operator << (ostream& os, const BusesForStopResponse& r) {
    if (r.buses_for_stop.empty()) {
        os << "No stop";
        return os;
    }
    bool first = true;

    for(const string& bus_for_stop: r.buses_for_stop) {
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
    vector<string> buses_to_stops;
    string bus;
};

ostream& operator << (ostream& os, const StopsForBusResponse& r) {
    if (r.buses_to_stops.empty()) {
        os << "No bus";
        return os;
    }

    for (const string& stop : r.buses_to_stops) {
        os << "Stop " << stop << ": ";
        if (r.buses_to_stops.size() == 1) {
            os << "no interchange";
        } else {
            for (const string& other_bus : r.buses_to_stops) {
                if (r.bus != other_bus) {
                    os << other_bus << " ";
                }
            }
        }
        os << endl;
    }
    return os;
}

struct AllBusesResponse {
    map<string, vector<string>> all_buses;
};

ostream& operator << (ostream& os, const AllBusesResponse& r) {

    if (r.all_buses.empty()) {
        os << "No buses";
    } else {
        for (const auto& bus_item : r.all_buses) {
            os << "Bus " << bus_item.first << ": ";
            for (const string& stop : bus_item.second) {
                os << stop << " ";
            }
            os << endl;
        }
    }
    return os;
}

class BusManager {
public:
    void AddBus(const string& bus, const vector<string>& stops_) {
        //cout << stops_ << endl;
        for(const string& stop: stops_) {
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

    BusesForStopResponse GetBusesForStop(const string& stop) const {
        if (stops_to_buses.count(stop) == 0) {
            return BusesForStopResponse{{}};
        } else {
            return BusesForStopResponse{stops_to_buses.at(stop)};
        }
    }

    StopsForBusResponse GetStopsForBus(const string& bus) const {
        if (buses_to_stops.count(bus) == 0) {
            return StopsForBusResponse{{}, bus};
        } else {
            return StopsForBusResponse{buses_to_stops.at(bus), bus};
        }
    }

    AllBusesResponse GetAllBuses() const {
        return AllBusesResponse{buses_to_stops};
    }
private:
    map<string, vector<string>> buses_to_stops, stops_to_buses;
};



int main() {

    int query_count;
    Query q;
    cin >> query_count;
    BusManager bm;
    for (int i = 0; i < query_count; ++i) {
        cin >> q;
        switch (q.type) {
            case QueryType::NewBus:
                bm.AddBus(q.bus, q.stops);
                break;
            case QueryType::BusesForStop:
                cout << bm.GetBusesForStop(q.stop) << endl;
                break;
            case QueryType::StopsForBus:
                cout << bm.GetStopsForBus(q.bus) << endl;
                break;
            case QueryType::AllBuses:
                cout << bm.GetAllBuses() << endl;
                break;
        }
    }

    return 0;
}


