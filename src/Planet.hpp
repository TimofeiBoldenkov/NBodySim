#ifndef GUARD_Planet
#define GUARD_Planet

#include <SFML/Graphics.hpp>
#include "Vector2Utils.hpp"

// Represents a planet, which have mass, speed, position and shape of type CircleShape.
// Although the CircleShape class also contains position, the Planet class contains position itself.
// The position the Planet class contains is sf::Vector2<double>, not sf::Vector2<float>.
// All the calculations are performed in double.
class Planet {
public:
    // Creates a Planet object from mass, speed, position, and shape.
    // The default CircleShape constructor is called if a user hasn't specified shape.
    // The position the shape that the parameter contains does not influence the position of the new Planet object.
    Planet(double mass, const sf::Vector2<double>& speed, const sf::Vector2<double>& position, const sf::CircleShape& shape = sf::CircleShape());

    // draws the planet to specified sf::RenderWindow
    void draw(sf::RenderWindow& window) const;

    // Updates the position of the planet (and of the shape)
    // in accordance with the speed of the planet and the elapsed time.
    // i.e. new position = old position + speed * elapsedTime
    void update(const sf::Time& elapsedTime);

    // Returns a copy of the mass of the planet.
    double getMass() const {
        return mass;
    }
    // Sets the mass of the object to a new value.
    void setMass(double mass) {
        this->mass = mass;
    }

    // Returns a copy of the speed of the planet.
    sf::Vector2<double> getSpeed() const {
        return speed;
    }
    // Sets the speed of the planet to a new value.
    void setSpeed(const sf::Vector2<double>& speed) {
        this->speed = speed;
    }

    // Returns a copy of the shape of the planet.
    sf::CircleShape getShape() const {
        return shape;
    }
    // Sets the shape of the object to a new value.
    // Changes the position of the planet in accordance with the position of the shape.
    void setShapeWithPosition(const sf::CircleShape& shape) {
        this->shape = shape;
        position = Vector2Utils::convert<double>(shape.getPosition());
    }
    // Sets the shape of the object to a new value.
    // The position of the planet does not change.
    // The position of the shape changes in accordance with the position of the planet.
    void setShapeWithoutPosition(const sf::CircleShape& shape) {
        this->shape = shape;
        this->shape.setPosition(Vector2Utils::convert<float>(position));
    }

    // Returns a copy of the position of the planet.
    sf::Vector2<double> getPosition() const {
        return position;
    }
    // Sets the position of the planet to a new value.
    void setPosition(const sf::Vector2<double>& position) {
        this->position = position;
        shape.setPosition(Vector2Utils::convert<float>(position));
    }

    // Sets the speed of the planet to a new value in accordance with the acceleration and the elapsed time.
    // i.e. new speed = old speed + acceleration * elapsed time
    void accelerate(const sf::Vector2<double>& acceleration, const sf::Time& time);


    // Calculates the displacement vector from planet1 to planet2.
    static sf::Vector2<double> displacement(const Planet& planet1, const Planet& planet2);

    // Calculates distance between two planets.
    // The result is the same if you call Vector2Utils::magnitude(displacement(planet1, planet2)).
    static double distance(const Planet& planet1, const Planet& planet2);

    // Calculates the force of gravity between two planets in accordance with given planets and the gravitational constante
    static sf::Vector2<double> forceOfGravity(const Planet& planet1, const Planet& planet2, double G);

private:
    double mass;
    sf::Vector2<double> speed;
    sf::Vector2<double> position;
    sf::CircleShape shape;
};

#endif
