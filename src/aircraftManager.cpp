#include "aircraftManager.hpp"

#include "aircraft.hpp"

#include <memory>
#include <utility>

void AircraftManager::move()
{
    for (auto it = aircrafts.begin(); it != aircrafts.end();)
    {
        auto& object = *it;
        object->move();
        if (object->toDelete())
        {
            it = aircrafts.erase(it);
        }
        else
        {
            it++;
        }
    }
}

void AircraftManager::add(std::unique_ptr<Aircraft> aircraft)
{
    aircrafts.emplace_back(std::move(aircraft));
}