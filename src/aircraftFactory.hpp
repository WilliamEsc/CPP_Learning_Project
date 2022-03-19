#pragma once

#include "aircraft.hpp"
#include "aircraft_types.hpp"

#include <string>
#include <set>

class AircraftFactory
{
private:
    std::set<std::string> airflight_number_set = {};
    std::string airlines[8] = { "AF", "LH", "EY", "DL", "KL", "BA", "AY", "EY" };
    AircraftType* aircraft_types[3] {};

public:

    void init_aircraft_types();
    std::unique_ptr<Aircraft> create_aircraft(const AircraftType& type, Tower& tower);
    std::unique_ptr<Aircraft> create_random_aircraft(Tower& tower);
};