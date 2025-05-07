#include <iostream>
#include "Universe.hpp"

void Universe::draw(sf::RenderWindow& window) const
{
    for (Planet planet : planets) {
        planet.draw(window);
    }
}

void Universe::move(sf::Time time)
{
    for (Planet planet : planets) {
        planet.move(time);
    }
}

void Universe::addPlanet(Planet planet)
{
    planets.push_back(planet);
}
