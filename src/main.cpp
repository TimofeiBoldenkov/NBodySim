#include <unordered_map>
#include <iostream>
#include "Universe.hpp"
#include "utils.hpp"
#include "KeyboardHandler.hpp"

int main()
{
    Universe universe(1000);

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

            i++;
        } catch (std::invalid_argument) {
            std::clog << "Invalid input. Please enter valid data." << std::endl;
        }
    }

    sf::VideoMode videoMode(1920, 1080);
    sf::RenderWindow window(videoMode, "Physical Simulation");
    sf::View view(utils::convenientView(universe, videoMode));
    view.zoom(2);
    window.setView(view);
    
    const sf::Time kMinStep = sf::milliseconds(5);
    KeyboardHandler keyboardHandler;

    universe.restartClock();
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::MouseWheelScrolled) {
                view.zoom(std::pow(0.9, event.mouseWheelScroll.delta));
                window.setView(view);
            }

            if (event.type == sf::Event::KeyPressed && event.type == sf::Event::KeyReleased) {
                keyboardHandler.update(event);
            }

            if (event.type == sf::Event::Closed)
                window.close();
        }

        const KeyInfo& keyInfo = keyboardHandler.keyInfo(sf::Keyboard::Key::Right);
        if (keyInfo.pressed) {
            view.move(view.getSize().x * keyInfo.clock.restart().asSeconds() / 5, 0);
            window.setView(view);
        } 
        if (pressed[sf::Keyboard::Key::Left]) {
            view.move(-view.getSize().x * clocks[sf::Keyboard::Key::Left].restart().asSeconds() / 5, 0);
            window.setView(view);
        } 
        if (pressed[sf::Keyboard::Key::Up]) {
            view.move(0, -view.getSize().x * clocks[sf::Keyboard::Key::Up].restart().asSeconds() / 5);
            window.setView(view);
        } 
        if (pressed[sf::Keyboard::Key::Down]) {
            view.move(0, view.getSize().x * clocks[sf::Keyboard::Key::Down].restart().asSeconds() / 5);
            window.setView(view);
        }

        if (universe.elapsedTime() > kMinStep) {
            universe.update();
        }

        window.clear(sf::Color::Black);
        universe.draw(window);
        window.display();
    }

    return 0;
}
