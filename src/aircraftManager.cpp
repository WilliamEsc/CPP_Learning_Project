#include "aircraftManager.hpp"

#include "aircraft.hpp"

#include <algorithm>
#include <memory>
#include <utility>

void AircraftManager::move()
{
    std::sort(aircrafts.begin(), aircrafts.end(),
              [](std::unique_ptr<Aircraft>& ar1, std::unique_ptr<Aircraft>& ar2)
              {
                  if (!ar1->has_terminal() && ar2->has_terminal())
                  {
                      return false;
                  }
                  if (ar1->has_terminal() && !ar2->has_terminal())
                  {
                      return true;
                  }
                  return ar1->getFuel() < ar2->getFuel();
              });
    aircrafts.erase(std::remove_if(aircrafts.begin(), aircrafts.end(),
                                   [](std::unique_ptr<Aircraft>& aircraft)
                                   {
                                       aircraft->move();
                                       return aircraft->toDelete();
                                   }),
                    aircrafts.end());
}

void AircraftManager::add(std::unique_ptr<Aircraft> aircraft)
{
    aircrafts.emplace_back(std::move(aircraft));
    for (const auto& e : aircrafts)
    {
        std::cout << " reserved : " << e->has_terminal() << " fuel : " << e->getFuel() << std::endl;
    }
}

int AircraftManager::count_airlines(const std::string& airline) const
{
    return std::count_if(aircrafts.begin(), aircrafts.end(),
                         [airline](const std::unique_ptr<Aircraft>& aircraft)
                         { return aircraft->flightNumber().rfind(airline, 0) == 0; });
}

int AircraftManager::get_required_fuel() const
{
    std::reduce(aircrafts.begin(), aircrafts.end(), 0,
                [](int v1, const std::unique_ptr<Aircraft>& aircraft)
                {
                    if (aircraft->is_low_on_fuel() && aircraft->at_terminal())
                    {
                        return v1 + 3000 - aircraft->getFuel();
                    }
                    return v1;
                });
}