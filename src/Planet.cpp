#include <cmath>
#include "Planet.hpp"
#include "Vector2Utils.hpp"

Planet::Planet(double mass_, const sf::Vector2<double>& speed_, const sf::Vector2<double>& position_, const sf::CircleShape& shape_)
               : mass(mass_), speed(speed_), position(position_), shape(shape_)
{
    shape.setPosition(Vector2Utils::convert<float>(position_));
    float radius = std::pow(mass_, 1.f/2) / 10;
    shape.setRadius(radius);
    shape.setOrigin({radius, radius});
}

void Planet::update(const sf::Time& time) 
{
    position += speed * static_cast<double>(time.asSeconds());
    shape.setPosition(Vector2Utils::convert<float>(position));
}

void Planet::draw(sf::RenderWindow& window) const {
    window.draw(shape);
}

void Planet::accelerate(const sf::Vector2<double>& acceleration, const sf::Time& time)
{
    speed += acceleration * static_cast<double>(time.asSeconds());
}

sf::Vector2<double> Planet::displacement(const Planet& planet1, const Planet& planet2)
{
    return planet2.getPosition() - planet1.getPosition();
}

double Planet::distance(const Planet& planet1, const Planet& planet2)
{
    return Vector2Utils::magnitude(displacement(planet1, planet2));
}

sf::Vector2<double> Planet::forceOfGravity(const Planet& planet1, const Planet& planet2, double G)
{
    sf::Vector2<double> disp = displacement(planet1, planet2);
    double forceMagnitude = G * planet1.getMass() * planet2.getMass() / std::pow(Vector2Utils::magnitude(disp), 2);

    return Vector2Utils::directionalVector(forceMagnitude, disp);
}
