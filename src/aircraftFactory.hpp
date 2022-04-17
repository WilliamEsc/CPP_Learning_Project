#pragma once

#include "aircraft.hpp"
#include "aircraft_types.hpp"

#include <set>
#include <string>

class AircraftFactory
{
private:
    std::set<std::string> airflight_number_set = {};
    std::string airlines[8]                    = { "AF", "LH", "EY", "DL", "KL", "BA", "AY", "EY" };
    std::array<AircraftType, 3> aircraft_types;

public:
    AircraftFactory() :
        aircraft_types { AircraftType { .02f, .05f, .02f, MediaPath { "l1011_48px.png" } },
                         AircraftType { .02f, .05f, .02f, MediaPath { "b707_jat.png" } },
                         AircraftType { .02f, .08f, .03f, MediaPath { "concorde_af.png" } } }
    {}
    std::unique_ptr<Aircraft> create_aircraft(const AircraftType& type, Tower& tower);
    std::unique_ptr<Aircraft> create_random_aircraft(Tower& tower);
    const std::string airline(const int index) const;
};