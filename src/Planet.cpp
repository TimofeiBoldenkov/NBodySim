#include "Planet.hpp"

Planet::Planet(float mss, sf::Vector2f spd, float radius, std::size_t pointCount) 
               : mass(mss), speed(spd), shape(radius, pointCount) 
{
    shape.setOrigin({radius, radius});
}

Planet::Planet(float mss, sf::Vector2f spd, sf::CircleShape shp) 
               : mass(mss), speed(spd), shape(shp) { }

void Planet::move(sf::Time time) 
{
    shape.move(speed * time.asSeconds());
}
