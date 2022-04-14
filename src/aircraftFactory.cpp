#include "aircraftFactory.hpp"

std::unique_ptr<Aircraft> AircraftFactory::create_aircraft(const AircraftType& type, Tower& tower)
{
    std::string number = airlines[std::rand() % 8] + std::to_string(1000 + (rand() % 9000));
    while (airflight_number_set.find(number) != airflight_number_set.end())
    {
        number = airlines[std::rand() % 8] + std::to_string(1000 + (rand() % 9000));
    }
    const std::string flight_number = number;
    assert(
        !(airflight_number_set.find(flight_number) != airflight_number_set.end())); // très con comme assert
    airflight_number_set.emplace(flight_number);
    const float angle       = (rand() % 1000) * 2 * 3.141592f / 1000.f; // random angle between 0 and 2pi
    const Point3D start     = Point3D { std::sin(angle), std::cos(angle), 0 } * 3 + Point3D { 0, 0, 2 };
    const Point3D direction = (-start).normalize();

    return std::make_unique<Aircraft>(type, flight_number, start, direction, tower, (rand() % 2850) + 150);
}

std::unique_ptr<Aircraft> AircraftFactory::create_random_aircraft(Tower& tower)
{
    return create_aircraft(aircraft_types[rand() % 3], tower);
}

const std::string AircraftFactory::airline(const int index) const
{
    assert((index >= 0 && index < 8));
    return airlines[index];
}