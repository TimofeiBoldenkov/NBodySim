#ifndef GUARD_Planet
#define GUARD_Planet

#include <SFML/Graphics.hpp>
#include "Vector2Utils.hpp"

// Represents a planet, which has mass, velocity, position and a visual representation using sf::CircleShape.
// Although sf::CircleShape contains its own position (as sf::Vector2<float>),
// the Planet class maintains a separate position stored as sf::Vector2<double> for higher precision.
// All physics calculations are performed using double precision.
// The CircleShape is used solely for rendering purposes and is updated to match the precise position.
class Planet {
public:
    // Creates a Planet object from mass, velocity, position, and shape.
    // The default CircleShape constructor is called if the user hasn't specified a shape.
    // The position contained in the provided shape does not affect the position of the new Planet object.
    // Radius = mass ** (1/3) / 3 by default
    Planet(double mass, const sf::Vector2<double>& velocity, const sf::Vector2<double>& position, const sf::CircleShape& shape = sf::CircleShape());

    // Draws the Planet to the specified sf::RenderWindow.
    void draw(sf::RenderWindow& window) const;

    // Updates the position of the Planet (as well as its shape)
    // according to its velocity and the elapsed time.
    // i.e., new position = old position + velocity * elapsedTime
    void update(const sf::Time& elapsedTime);

    // Returns the Planet's mass.
    double getMass() const {
        return mass;
    }
    // Sets the Planet's mass to the specified value.
    void setMass(double mass) {
        this->mass = mass;
    }

    // Returns the Planet's velocity.
    sf::Vector2<double> getVelocity() const {
        return velocity;
    }
    // Sets the velocity of the planet to the specified value.
    void setVelocity(const sf::Vector2<double>& velocity) {
        this->velocity = velocity;
    }

    // Returns the Planet's shape.
    sf::CircleShape getShape() const {
        return shape;
    }
    // Sets the Planet's shape to the specified value.
    // Updates the Planet's position to match the shape's position.
    void setShapeWithPosition(const sf::CircleShape& shape) {
        this->shape = shape;
        position = Vector2Utils::convert<double>(shape.getPosition());
    }
    // Sets the Planet's shape to the specified value.
    // The Planet's position remains unchanged.
    // The shape's position is updated to match the Planet's position.
    void setShapeWithoutPosition(const sf::CircleShape& shape) {
        this->shape = shape;
        this->shape.setPosition(Vector2Utils::convert<float>(position));
    }

    // Returns the Planet's position. 
    sf::Vector2<double> getPosition() const {
        return position;
    }
    // Sets the Planet's position to the specified value.
    // The shape's position is updated to match the Planet's position.
    void setPosition(const sf::Vector2<double>& position) {
        this->position = position;
        shape.setPosition(Vector2Utils::convert<float>(position));
    }

    // Sets the Planet's velocity to a new value according to the acceleration and the elapsed time.
    // i.e., new velocity = old velocity + acceleration * elapsedTime
    void accelerate(const sf::Vector2<double>& acceleration, const sf::Time& elapsedTime);


    // Calculates the displacement vector from planet1 to planet2.
    static sf::Vector2<double> displacement(const Planet& planet1, const Planet& planet2);

    // Calculates distance between the two planets.
    // This is equivalent to calling Vector2Utils::magnitude(displacement(planet1, planet2)).
    static double distance(const Planet& planet1, const Planet& planet2);

    // Calculates the gravitational force between two planets based on the given planets and gravitational constant.
    static sf::Vector2<double> forceOfGravity(const Planet& planet1, const Planet& planet2, double G);

private:
    double mass;
    sf::Vector2<double> velocity;
    sf::Vector2<double> position;
    sf::CircleShape shape;
};

#endif
