#include <iostream>
#include "Universe.hpp"

void Universe::draw(sf::RenderWindow& window) const
{
    for (const Planet& planet : planets) {
        planet.draw(window);
    }
}

void Universe::move(sf::Time time)
{
    for (Planet& planet : planets) {
        planet.move(time);
    }
}

void Universe::addPlanet(Planet planet)
{
    planets.push_back(planet);
}


sf::Vector2f Universe::acceleration(std::vector<Planet>::const_iterator iter) const
{
    sf::Vector2f force = {0, 0};

    for (std::vector<Planet>::const_iterator other = planets.begin(); iter != planets.end(); iter++) {
        if (other == iter)
            continue;
        
        force += Planet::forceOfGravity(*iter, *other);
    }

    return force / iter->getMass();
}
