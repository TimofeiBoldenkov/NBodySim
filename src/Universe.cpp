#include <iostream>
#include "Universe.hpp"
#include "Vector2Utils.hpp"

void Universe::draw(sf::RenderWindow& window) const
{
    for (const Planet& planet : planets) {
        planet.draw(window);
    }
}

void Universe::update(float timeFactor)
{
    sf::Time time = clock.restart();
    for (std::vector<Planet>::size_type i = 0; i < planets.size(); i++) {
        planets[i].accelerate(acceleration(i), time * timeFactor);
        planets[i].update(time * timeFactor);
    }
}

void Universe::addPlanet(const Planet& planet)
{
    planets.push_back(planet);
}

sf::Vector2<double> Universe::forceOfGravity(std::vector<Planet>::const_iterator planet1, std::vector<Planet>::const_iterator planet2) const
{
    return Planet::forceOfGravity(*planet1, *planet2, G);
}

sf::Vector2<double> Universe::acceleration(std::vector<Planet>::const_iterator planet) const
{
    sf::Vector2<double> force = {0, 0};

    for (std::vector<Planet>::const_iterator other = planets.begin(); other != planets.end(); other++) {
        if (other == planet)
            continue;
        
        force += forceOfGravity(planet, other);
    }

    return force / planet->getMass();
}
