#ifndef GUARD_Planet
#define GUARD_Planet

#include <SFML/Graphics.hpp>

class Planet {
public:
    Planet(float mass, sf::Vector2f spd, float radius, std::size_t pointCount = 30);
    Planet(float mass, sf::Vector2f spd, sf::CircleShape);

    void draw(sf::RenderWindow& window) const {
        window.draw(shape);
    }

    void move(sf::Time);

    sf::Vector2f getSpeed() const {
        return speed;
    }

    void setSpeed(float x, float y) {
        speed = sf::Vector2f(x, y);
    }

    float getRadius() const {
        return shape.getRadius();
    }

    sf::Vector2f getPosition() const {
        return shape.getPosition();
    }

    sf::Color getColor() const {
        return shape.getFillColor();
    }

    void setColor(sf::Color color) {
        shape.setFillColor(color);
    }

private:
    float mass;
    sf::Vector2f speed;
    sf::CircleShape shape;
};

#endif
