#include <catch2/catch_test_macros.hpp>
#include <Universe.hpp>
#include <thread>
#include <chrono>

TEST_CASE("Invalid planet in a system", "[invalid]")
{
    Universe universe(1);

    universe.addPlanet(Planet(100, {0, 0}, {std::nan(""), 0})); // Add an invalid planet
    universe.addPlanet(Planet(100, {0, 0}, {100, 100}));
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
    universe.update(100);
    REQUIRE(universe[1].getPosition() == sf::Vector2<double>(100, 100)); // An invalid planet does not affect other planets.
}


