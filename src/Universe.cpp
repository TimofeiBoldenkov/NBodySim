#include <iostream>
#include <Universe.hpp>
#include <Vector2Utils.hpp>

void Universe::draw(sf::RenderWindow& window) const
{
    // Draw all the planets of the universe.
    for (const Planet& planet : planets) {
        planet.draw(window);
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

sf::Vector2<double> Universe::totalForceOnPlanet(std::vector<Planet>::const_iterator planet) const
{
    sf::Vector2<double> force = {0, 0};

    for (std::vector<Planet>::const_iterator other = planets.begin(); other != planets.end(); other++) {
        if (other == planet || !other->isValid())
            continue;

        // Construct the total force acting on the Planet from the sum of all individual forces.
        force += forceOfGravity(planet, other);
    }

    return force;
}

void Universe::update(float timeFactor)
{
    sf::Time time = clock.restart(); // clock.restart() returns the time elapsed since the last restart() call.
    for (std::vector<Planet>::size_type i = 0; i < planets.size(); i++) {
        planets[i].applyForce(totalForceOnPlanet(i), time * timeFactor); // Accelerate all the planets.
        planets[i].update(time * timeFactor); // Move all the planets according to the new speed.
    }
}
