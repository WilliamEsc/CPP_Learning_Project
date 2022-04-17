#include "tower_sim.hpp"

#include "GL/opengl_interface.hpp"
#include "aircraft.hpp"
#include "aircraftFactory.hpp"
#include "aircraftManager.hpp"
#include "airport.hpp"
#include "config.hpp"
#include "img/image.hpp"
#include "img/media_path.hpp"

#include <cassert>
#include <cstdlib>
#include <ctime>
#include <memory>
#include <utility>

using namespace std::string_literals;

TowerSimulation::TowerSimulation(int argc, char** argv) :
    help { (argc > 1) && (std::string { argv[1] } == "--help"s || std::string { argv[1] } == "-h"s) },
    context_Initializer(argc, argv)
{
    GL::move_queue.emplace(&aircraft_manager);

    create_keystrokes();
}

TowerSimulation::~TowerSimulation()
{
    delete airport;
}

void TowerSimulation::create_keystrokes()
{
    GL::keystrokes.emplace('x', []() { GL::exit_loop(); });
    GL::keystrokes.emplace('q', []() { GL::exit_loop(); });
    GL::keystrokes.emplace(
        'c',
        [this]() { aircraft_manager.add(aircraft_factory.create_random_aircraft(airport->get_tower())); });
    GL::keystrokes.emplace('+', []() { GL::change_zoom(0.95f); });
    GL::keystrokes.emplace('-', []() { GL::change_zoom(1.05f); });
    GL::keystrokes.emplace('f', []() { GL::toggle_fullscreen(); });
    GL::keystrokes.emplace('o', []() { GL::up_framerate(); });
    GL::keystrokes.emplace('l', []() { GL::down_framerate(); });
    GL::keystrokes.emplace('p', []() { GL::pause(); });
    GL::keystrokes.emplace('m', [this]() { std::cout << aircraft_manager.get_nbCrash() << std::endl; });
    for (char i = '0'; i < '8'; i++)
    {
        GL::keystrokes.emplace(i,
                               [this, i]() {
                                   std::cout
                                       << aircraft_manager.count_airlines(aircraft_factory.airline(i - '0'))
                                       << std::endl;
                               });
    }
}

void TowerSimulation::display_help() const
{
    std::cout << "This is an airport tower simulator" << std::endl
              << "the following keysstrokes have meaning:" << std::endl;

    for (const auto& [key, value] : GL::keystrokes)
    {
        std::cout << key << ' ';
    }

    std::cout << std::endl;
}

void TowerSimulation::init_airport()
{
    assert(airport == nullptr);
    airport =
        new Airport { one_lane_airport, Point3D { 0, 0, 0 },
                      new img::Image { one_lane_airport_sprite_path.get_full_path() }, aircraft_manager };

    GL::move_queue.emplace(airport);
}

void TowerSimulation::launch()
{
    if (help)
    {
        display_help();
    }

    init_airport();
    GL::loop();
}
