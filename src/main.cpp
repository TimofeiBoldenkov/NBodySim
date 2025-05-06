#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

class Ball {
    friend bool reflectOnCollision(Ball ball1, Ball ball2);
public:
    sf::CircleShape shape;
    sf::Vector2f speed;

    Ball(sf::CircleShape sh, sf::Vector2f sp) : shape(sh), speed(sp) { }
    Ball(float radius, sf::Vector2f sp) : shape(radius), speed(sp) { }

    void move() {
        shape.move(speed);
    }

    void reflectX() {
        speed.x = -speed.x;
    }
    void reflectY() {
        speed.y = -speed.y;
    }

    void reflectOnBorder(const sf::Vector2u windowSize) {


        if (speed.x > 0 && shape.getPosition().x + shape.getRadius() * 2 + speed.x > windowSize.x ||
            speed.x < 0 && shape.getPosition().x + speed.x < 0)
            reflectX();
        if (speed.y > 0 && shape.getPosition().y + shape.getRadius() * 2 + speed.y > windowSize.y ||
            speed.y < 0 && shape.getPosition().y + speed.y < 0)
            reflectY();
    }

private:
};

bool reflectOnCollision(Ball ball1, Ball ball2) 
{

}

int main()
{
    sf::RenderWindow window({1920, 1080}, "Physical Simulation");

    Ball ball1(50, {15, 10});
    ball1.shape.setFillColor(sf::Color::Green);

    Ball ball2(70, {7, 9});
    ball2.shape.setFillColor(sf::Color::Blue);

    while (window.isOpen()) {
        sf::Event event;

        while (window.pollEvent(event)) {
            
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        ball1.reflectOnBorder(window.getSize());
        ball2.reflectOnBorder(window.getSize());

        ball1.move();
        ball2.move();

        window.clear();
        window.draw(ball1.shape);
        window.draw(ball2.shape);
        window.display();

        sf::sleep(sf::milliseconds(10));
    }
}
