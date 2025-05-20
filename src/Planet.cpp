#include <cmath>
#include <Planet.hpp>
#include <Vector2Utils.hpp>
#include <iostream>

Planet::Planet(double mass_, const sf::Vector2<double>& velocity_, const sf::Vector2<double>& position_, const sf::CircleShape& shape_)
               : mass(mass_), velocity(velocity_), position(position_), shape(shape_)
{
    shape.setPosition(Vector2Utils::convert<float>(position_)); // sf::CircleShape stores its position as an sf::Vector2<float>.
    float radius = std::pow(std::abs(mass_), 1.f/3) / 3;
    shape.setRadius(radius);
    shape.setOrigin({radius, radius}); // Calculate the shape's position, zoom, rotation, etc. relative to its centre
}

void Planet::update(const sf::Time& time) 
{
    position += velocity * static_cast<double>(time.asSeconds()); // Move according to the Planet's speed and the elapsed time
    shape.setPosition(Vector2Utils::convert<float>(position));
}

void Planet::draw(sf::RenderWindow& window) const
{
    if (isValid())
        window.draw(shape);
}

bool Planet::isValid() const
{
    if (!std::isfinite(position.x) || !std::isfinite(position.y) || !std::isfinite(mass) || mass == 0)
        return false;
    else
        return true;
}

void Planet::accelerate(const sf::Vector2<double>& acceleration, const sf::Time& time)
{
    velocity += acceleration * static_cast<double>(time.asSeconds());
}

void Planet::applyForce(const sf::Vector2<double>& force, const sf::Time& time)
{
    // Newton's second law of motion: F = m * a => a = F / m
    accelerate(force / mass, time);
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

    // Newton's law of universal gravitation: F = G * m1 * m2 / r ** 2
    double forceMagnitude = G * planet1.getMass() * planet2.getMass() / std::pow(Vector2Utils::magnitude(disp), 2);

    // The vector of the gravitational force is directed from one object to the other.
    return Vector2Utils::directionalVector(forceMagnitude, disp);
}
