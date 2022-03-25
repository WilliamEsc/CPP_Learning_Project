#pragma once

#include "GL/dynamic_object.hpp"

#include <memory>
#include <vector>

class Aircraft;

class AircraftManager : public GL::DynamicObject
{
private:
    std::vector<std::unique_ptr<Aircraft>> aircrafts;

public:
    void move() override;
    void add(std::unique_ptr<Aircraft> aircraft);
    int count_airlines(const std::string& airline) const;
    int get_required_fuel() const;
};