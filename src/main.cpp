#include <iostream>
#include "Universe.hpp"
#include "utils.hpp"

int main()
{
    Universe universe(1000);
    sf::Clock clock;

    float minX, maxX, minY, maxY;
    int i = 0;
    while (std::cin) {
        std::string line;
        std::vector<std::string> words;

        try {
            std::cout << "Mass of planet " << i + 1 << " (leave blank if you don't want to add any new planets): ";
            std::getline(std::cin, line);
            if (utils::isSpace(line))
                break;
            
            if ((words = utils::split(line)).size() != 1) {
                throw std::invalid_argument("improper number of arguments");
            }
            double mass = std::stod(words[0]);

            std::cout << "Speed of planet " << i + 1 << " (x y): ";
            std::getline(std::cin, line);
            if ((words = utils::split(line)).size() != 2) {
                throw std::invalid_argument("improper number of arguments");
            }
            sf::Vector2<double> speed;
            speed.x = std::stod(words[0]);
            speed.y = std::stod(words[1]);


            std::cout << "Position of planet " << i + 1 << " (x y): ";
            std::getline(std::cin, line);
            if ((words = utils::split(line)).size() != 2) {
                throw std::invalid_argument("incorrect number of inputs");
            }
            sf::Vector2<double> position;
            position.x = std::stod(words[0]);
            position.y = std::stod(words[1]);

            universe.addPlanet(Planet(mass, speed, position));

            float radius = universe[i].getShape().getRadius();
            if (i == 0) {
                minX = position.x - radius;
                maxX = position.x + radius;
                minY = position.y - radius;
                maxX = position.y + radius;
            } else {
                if (position.x - radius < minX) minX = position.x - radius;
                else if (position.x + radius > maxX) maxX = position.x + radius;
                if (position.y - radius < minY) minY = position.y - radius;
                else if (position.y + radius > maxY) maxY = position.y + radius;
            }

            i++;
        } catch (std::invalid_argument) {
            std::clog << "Invalid input. Please enter valid data." << std::endl;
        }
    }

    sf::VideoMode videoMode(1920, 1080);
    sf::RenderWindow window(videoMode, "Physical Simulation");
    sf::View view(utils::viewForVideoMode({minX, minY, maxX - minX, maxY - minY}, videoMode));
    view.zoom(2);
    window.setView(view);

    const sf::Time kMinStep = sf::milliseconds(5);

    bool rightPressed = false;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::MouseWheelScrolled) {
                view.zoom(std::pow(0.9, event.mouseWheelScroll.delta));
                window.setView(view);
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                view.move(view.getSize().x * clock.getElapsedTime().asSeconds(), 0);
                window.setView(view);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                view.move(-view.getSize().x * clock.getElapsedTime().asSeconds(), 0);
                window.setView(view);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                view.move(0, -view.getSize().x * clock.getElapsedTime().asSeconds());
                window.setView(view);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                view.move(0, view.getSize().x * clock.getElapsedTime().asSeconds());
                window.setView(view);
            }

            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (clock.getElapsedTime() > kMinStep) {
            universe.update(clock.restart());
        }

        window.clear(sf::Color::Black);
        universe.draw(window);
        window.display();
    }

    return 0;
}
