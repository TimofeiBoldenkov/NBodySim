#include <iostream>
#include "Universe.hpp"
#include "Vector2Utils.hpp"

void Universe::draw(sf::RenderWindow& window) const
{
    for (const Planet& planet : planets) {
        planet.draw(window);
    }
}

void Universe::update(const sf::Time& time)
{
    for (std::vector<Planet>::size_type i = 0; i < planets.size(); i++) {
        planets[i].accelerate(acceleration(i), time);
        planets[i].update(time);
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
    // std::clog << "i: " << planet - planets.begin() << std::endl;

    sf::Vector2<double> force = {0, 0};

    for (std::vector<Planet>::const_iterator other = planets.begin(); other != planets.end(); other++) {
        if (other == planet)
            continue;
        
        force += forceOfGravity(planet, other);
    }

    // std::clog << "force: " << Vector2Utils::magnitude(force) << std::endl;
    // std::clog << "mass:  " << planet->getMass() << std::endl;
    return force / planet->getMass();
}
