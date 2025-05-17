#include <catch2/catch_test_macros.hpp>
#include "../src/Planet.hpp"
#include <SFML/Graphics.hpp>


TEST_CASE("Planet update", "[update]")
{
    Planet planet(1000, {100, 0}, {0, 0});

    planet.update(sf::seconds(1));
    REQUIRE(planet.getPosition().x == 100);
}

TEST_CASE("Planet accelerate", "[accelerate]")
{
    Planet planet(1000, {100, 0}, {0, 0});

    planet.accelerate({0, 100}, sf::seconds(1));
    REQUIRE(planet.getVelocity() == sf::Vector2<double>{100, 100});
}
