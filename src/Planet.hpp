#ifndef GUARD_Planet
#define GUARD_Planet

#include <SFML/Graphics.hpp>
#include "Vector2Utils.hpp"

class Planet {
public:
    Planet(double mass, const sf::Vector2<double>& speed, const sf::Vector2<double>& position, const sf::CircleShape& shape = sf::CircleShape());

    void draw(sf::RenderWindow& window) const;

    void update(const sf::Time&);

    double getMass() const {
        return mass;
    }
    void setMass(double mass) {
        this->mass = mass;
    }

    sf::Vector2<double> getSpeed() const {
        return speed;
    }

    void setSpeed(const sf::Vector2<double>& speed) {
        this->speed = speed;
    }

    sf::CircleShape getShape() const {
        return shape;
    }

    void setShape(const sf::CircleShape& shape) {
        this->shape = shape;
        position = Vector2Utils::convert<double>(shape.getPosition());
    }
    void setShapeWithoutPosition(const sf::CircleShape& shape) {
        this->shape = shape;
        this->shape.setPosition(Vector2Utils::convert<float>(position));
    }

    sf::Vector2<double> getPosition() const {
        return position;
    }
    void setPosition(const sf::Vector2<double>& position) {
        this->position = position;
        shape.setPosition(Vector2Utils::convert<float>(position));
    }

    void accelerate(const sf::Vector2<double>& acceleration, const sf::Time& time);

    static sf::Vector2<double> displacement(const Planet& planet1, const Planet& planet2);
    static double distance(const Planet& planet1, const Planet& planet2);
    static sf::Vector2<double> forceOfGravity(const Planet& planet1, const Planet& planet2, double G);

private:
    double mass;
    sf::Vector2<double> speed;
    sf::Vector2<double> position;
    sf::CircleShape shape;
};

#endif
