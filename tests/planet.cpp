#include <catch2/catch_test_macros.hpp>
#include <Planet.hpp>
#include <SFML/Graphics.hpp>
#include <limits>


TEST_CASE("Planet update", "[update]")
{
    Planet planet(1000, {100, 0}, {0, 0});

    planet.update(sf::seconds(1));
    REQUIRE(planet.getPosition() == sf::Vector2<double>(100, 0));
    planet.update(sf::seconds(0));
    REQUIRE(planet.getPosition() == sf::Vector2<double>(100, 0));
    planet.update(sf::seconds(-1));
    REQUIRE(planet.getPosition() == sf::Vector2<double>(0, 0));
    planet.setVelocity(sf::Vector2<double>(-100, 0));
    planet.update(sf::seconds(1));
    REQUIRE(planet.getPosition() == sf::Vector2<double>(-100, 0));
    REQUIRE(planet.getShape().getPosition() == sf::Vector2f(-100, 0));
    planet.setPosition({0, 0});
    REQUIRE(planet.getPosition() == sf::Vector2<double>(0, 0));
    REQUIRE(planet.getShape().getPosition() == sf::Vector2f(0, 0));
}

TEST_CASE("Planet accelerate", "[accelerate]")
{
    Planet planet(1000, {100, 0}, {0, 0});

    planet.accelerate({0, 100}, sf::seconds(1));
    REQUIRE(planet.getVelocity() == sf::Vector2<double>(100, 100));
    planet.accelerate({0, -100}, sf::seconds(-1));
    REQUIRE(planet.getVelocity() == sf::Vector2<double>(100, 200));
    planet.accelerate({10000, 10000}, sf::seconds(0));
    REQUIRE(planet.getVelocity() == sf::Vector2<double>(100, 200));
    planet.update(sf::seconds(0.5));
    REQUIRE(planet.getPosition() == sf::Vector2<double>(50, 100));
    REQUIRE(planet.getShape().getPosition() == sf::Vector2f(50, 100));
}

TEST_CASE("Planet set shape", "[setShape]")
{
    Planet planet(1000, {100, 0}, {200, 300});
    planet.setShapeWithoutPosition(sf::CircleShape(10));
    REQUIRE(planet.getPosition() == sf::Vector2<double>(200, 300));
    REQUIRE(planet.getShape().getPosition() == sf::Vector2f(200, 300));

    sf::CircleShape shape(10);
    shape.setPosition(-200, -100);
    planet.setShapeWithPosition(shape);
    REQUIRE(planet.getPosition() == sf::Vector2<double>(-200, -100));
    REQUIRE(planet.getShape().getPosition() == sf::Vector2f(-200, -100));
}

TEST_CASE("Planet displacement", "[displacement]")
{
    Planet planet1(1000, {320, 0}, {200, 130});
    Planet planet2(1000, {0, 110}, {300, 400});
    REQUIRE(Planet::displacement(planet1, planet2) == sf::Vector2<double>(100, 270));
    REQUIRE(Planet::displacement(planet2, planet1) == sf::Vector2<double>(-100, -270));
}

TEST_CASE("Planet distance", "[distance]")
{
    Planet planet1(1000, {320, 0}, {100, 200});
    Planet planet2(1000, {110, 23}, {400, 600});
    REQUIRE(Planet::distance(planet1, planet2) == 500);
    REQUIRE(Planet::distance(planet2, planet1) == 500);
}

TEST_CASE("Planet force of gravity" "[forceOfGravity]")
{
    const double G = 0.1;

    const double minPrecision = 1e-9; // Minimum precision

    Planet planet1(100, {213, 348}, {100, 200});
    Planet planet2(100, {432, 32}, {500, 500});
    REQUIRE(std::abs(Vector2Utils::magnitude(Planet::forceOfGravity(planet1, planet2, G)) - 0.004) < minPrecision);

    planet1.setPosition({0, 130});
    planet2.setPosition({200, 130});
    REQUIRE(std::abs(Planet::forceOfGravity(planet1, planet2, G).x - 0.025) < minPrecision);
    REQUIRE(std::abs(Planet::forceOfGravity(planet1, planet2, G).y - 0) < minPrecision);
    REQUIRE(std::abs(Planet::forceOfGravity(planet2, planet1, G).x - -0.025) < minPrecision);
    REQUIRE(std::abs(Planet::forceOfGravity(planet2, planet1, G).y - 0) < minPrecision);
    
    planet1.setMass(0);
    REQUIRE(Planet::forceOfGravity(planet1, planet2, G) == sf::Vector2<double>(0, 0));
    REQUIRE(Planet::forceOfGravity(planet2, planet1, G) == sf::Vector2<double>(0, 0));

    planet1.setPosition({100, 100});
    planet2.setPosition({100, 100});
    REQUIRE(std::isnan(Planet::forceOfGravity(planet1, planet2, G).x));
    REQUIRE(std::isnan(Planet::forceOfGravity(planet1, planet2, G).y));
}
