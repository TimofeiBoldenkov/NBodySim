#ifndef GUARD_Planet
#define GUARD_Planet

#include <SFML/Graphics.hpp>

class Planet {
public:
    Planet(float mass, sf::Vector2f speed, float radius = 30);
    Planet(float mass, sf::Vector2f speed, sf::CircleShape shape);

    void draw(sf::RenderWindow& window) const;

    void move(sf::Time);

    float getMass() const {
        return mass;
    }
    void setMass(float mass) {
        this->mass = mass;
    }

    sf::Vector2f getSpeed() const {
        return speed;
    }

    void setSpeed(float x, float y) {
        speed = sf::Vector2f(x, y);
    }

    sf::CircleShape getShape() const {
        return shape;
    }

    void setShape(const sf::CircleShape& shape) {
        this->shape = shape;
    }
    void setShape(sf::CircleShape&& shape) {
        this->shape = shape;
    }
    void setShapeWithoutPosition(const sf::CircleShape& shape) {
        sf::Vector2f position = shape.getPosition();
        this->shape = shape;
        this->shape.setPosition(position);
    }
    void setShapeWithoutPosition(sf::CircleShape&& shape) {
        sf::Vector2f position = shape.getPosition();
        this->shape = shape;
        this->shape.setPosition(position);
    }

    sf::Vector2f getPosition() const {
        return shape.getPosition();
    }
    void setPosition(sf::Vector2f position) {
        shape.setPosition(position);
    }

    static float distance(const Planet& planet1, const Planet& planet2);
    static sf::Vector2f displacement(const Planet& planet1, const Planet& planet2);
    static sf::Vector2f forceOfGravity(const Planet& planet1, const Planet& planet2);

private:
    float mass;
    sf::Vector2f speed;
    sf::CircleShape shape;
};

#endif
