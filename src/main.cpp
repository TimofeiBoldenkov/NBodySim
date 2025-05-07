#include <iostream>
#include "Universe.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Physical Simulation");

    Universe universe;
    sf::Clock clock;

    universe.addPlanet(Planet(10, {1000, 1000}, 10));
    universe.addPlanet(Planet(10, {700, 600}, 20));
    universe.addPlanet(Planet(10, {300, 900}, 30));

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::Blue);
        universe.move(clock.restart());
        universe.draw(window);
        window.display();

    }

    return 0;
}
