#include "aircraftManager.hpp"

#include "aircraft.hpp"

#include <memory>
#include <utility>
#include <algorithm>

void AircraftManager::move()
{
        aircrafts.erase(std::remove_if(aircrafts.begin(), aircrafts.end(), [](std::unique_ptr<Aircraft>& t) { t->move(); return t->toDelete(); }),
            aircrafts.end());
}

void AircraftManager::add(std::unique_ptr<Aircraft> aircraft)
{
    aircrafts.emplace_back(std::move(aircraft));
}