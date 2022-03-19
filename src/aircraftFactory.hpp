#pragma once

#include "aircraft.hpp"
#include "aircraft_types.hpp"

#include <string>

class AircraftFactory
{
private:
    std::string airlines[8] = { "AF", "LH", "EY", "DL", "KL", "BA", "AY", "EY" };
    AircraftType* aircraft_types[3] { new AircraftType { .02f, .05f, .02f, MediaPath { "l1011_48px.png" } },
                                      new AircraftType { .02f, .05f, .02f, MediaPath { "b707_jat.png" } },
                                      new AircraftType { .02f, .08f, .02f,
                                                         MediaPath { "concorde_af.png" } } };

public:
    std::unique_ptr<Aircraft> create_aircraft(const AircraftType& type, const Tower& tower) const;
    std::unique_ptr<Aircraft> create_random_aircraft(const Tower& tower) const;
};