#include <cmath>
#include "Planet.hpp"
#include "Vector2.hpp"

Planet::Planet(float mss, sf::Vector2f spd, float radius) 
               : mass(mss), speed(spd), shape(radius)
{
    shape.setOrigin({radius, radius});
}

Planet::Planet(float mss, sf::Vector2f spd, sf::CircleShape shp) 
               : mass(mss), speed(spd), shape(shp) {
    shape.setOrigin({shp.getRadius(), shp.getRadius()});
}

void Planet::move(sf::Time time) 
{
    shape.move(speed * time.asSeconds());
}

void Planet::draw(sf::RenderWindow& window) const {
    window.draw(shape);
}

static sf::Vector2f displacement(const Planet& planet1, const Planet& planet2)
{
    return planet2.getPosition() - planet1.getPosition();
}

static float distance(const Planet& planet1, const Planet& planet2)
{
    return magnitude(displacement(planet1, planet2));
}

sf::Vector2f Planet::forceOfGravity(const Planet& planet1, const Planet& planet2)
{
    sf::Vector2f disp = displacement(planet1, planet2);
    float forceMagnitude = planet1.getMass() * planet2.getMass() / std::pow(magnitude(disp), 2);
    float k = std::sqrt(pow(forceMagnitude, 2) / (pow(disp.x, 2) + pow(disp.y, 2)));
    sf::Vector2f forceVector = disp;
    forceVector.x *= k;
    forceVector.y *= k;
}
