#include <unordered_map>
#include <iostream>
#include <thread>
#include <memory>
#include "Universe.hpp"
#include "utils.hpp"
#include "KeyboardHandler.hpp"

int main()
{
    // Create a Universe with G = 1000.
    // The higher G is, the faster planets move.
    Universe universe(1000);

    int i = 0; // The number of planets added so far
    while (std::cin) {
        std::string line; // A line of the user's input
        std::vector<std::string> words; // The line split into words.

        try {
            std::cout << "Mass of planet " << i + 1 << " (leave blank if you don't want to add any new planets): ";
            std::getline(std::cin, line);
            // Stop reading input if the line contains only the space characters.
            if (utils::isSpace(line))
                break;
            if ((words = utils::split(line)).size() != 1) {
                throw std::invalid_argument("improper number of arguments");
            }
            double mass = std::stod(words[0]);

            std::cout << "Velocity of planet " << i + 1 << " (x y): ";
            std::getline(std::cin, line);
            if ((words = utils::split(line)).size() != 2) {
                throw std::invalid_argument("improper number of arguments");
            }
            sf::Vector2<double> velocity;
            velocity.x = std::stod(words[0]);
            velocity.y = std::stod(words[1]);


            std::cout << "Position of planet " << i + 1 << " (x y): ";
            std::getline(std::cin, line);
            if ((words = utils::split(line)).size() != 2) {
                throw std::invalid_argument("incorrect number of inputs");
            }
            sf::Vector2<double> position;
            position.x = std::stod(words[0]);
            position.y = std::stod(words[1]);

            universe.addPlanet(Planet(mass, velocity, position));

            i++;
        } catch (std::invalid_argument) {
            std::clog << "Invalid input. Please enter valid data." << std::endl;
        }
    }

    sf::VideoMode videoMode(1700, 900);
    sf::RenderWindow window(videoMode, "Physical Simulation");
    sf::View view(utils::convenientView(universe, videoMode));
    view.zoom(2);
    window.setView(view);
    sf::View defaultView = window.getDefaultView();
    
    float timeFactor = 1;
    const sf::Time kMinStep = sf::milliseconds(5);
    KeyboardHandler keyboardHandler;

    sf::Font font;
    font.loadFromFile(PROJECT_SOURCE_DIR "/resources/Roboto-Regular.ttf");
    sf::Text timeFactorMessage("Time factor: " + std::to_string(timeFactor), font, videoMode.height / 50);
    timeFactorMessage.setFillColor(sf::Color::White);
    bool showTimeFactorMessage = false;

    std::unique_ptr<std::thread> calculationThread;

    universe.restartClock();

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::MouseWheelScrolled) {
                view.zoom(std::pow(0.9, event.mouseWheelScroll.delta));
                window.setView(view);
            }

            if (event.type == sf::Event::KeyPressed || event.type == sf::Event::KeyReleased) {
                keyboardHandler.update(event);
            }

            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (KeyInfo& keyInfo = keyboardHandler.keyInfo(sf::Keyboard::Key::Right); keyInfo.pressed) {
            view.move(view.getSize().x * keyInfo.clock.restart().asSeconds() / 5, 0);
            window.setView(view);
        } 
        if (KeyInfo& keyInfo = keyboardHandler.keyInfo(sf::Keyboard::Key::Left); keyInfo.pressed) {
            view.move(-view.getSize().x * keyInfo.clock.restart().asSeconds() / 5, 0);
            window.setView(view);
        } 
        if (KeyInfo& keyInfo = keyboardHandler.keyInfo(sf::Keyboard::Key::Up); keyInfo.pressed) {
            view.move(0, -view.getSize().x * keyInfo.clock.restart().asSeconds() / 5);
            window.setView(view);
        }
        if (KeyInfo& keyInfo = keyboardHandler.keyInfo(sf::Keyboard::Key::Down); keyInfo.pressed) {
            view.move(0, view.getSize().x * keyInfo.clock.restart().asSeconds() / 5);
            window.setView(view);
        }
        if (KeyInfo& keyInfo = keyboardHandler.keyInfo(sf::Keyboard::Key::F); keyInfo.pressed) {
            view.zoom(1 + keyInfo.clock.restart().asSeconds());
            window.setView(view);
        }
        if (KeyInfo& keyInfo = keyboardHandler.keyInfo(sf::Keyboard::Key::C); keyInfo.pressed) {
            view.zoom(1 - keyInfo.clock.restart().asSeconds());
            window.setView(view);
        }
        if (KeyInfo& keyInfo = keyboardHandler.keyInfo(sf::Keyboard::Key::Z); keyInfo.pressed) {
            timeFactor /= 1 + keyInfo.clock.restart().asSeconds();
            showTimeFactorMessage = true;
        }
        if (KeyInfo& keyInfo = keyboardHandler.keyInfo(sf::Keyboard::Key::X); keyInfo.pressed) {
            timeFactor *= 1 + keyInfo.clock.restart().asSeconds();
            showTimeFactorMessage = true;
        }

        
        if (universe.elapsedTime() > kMinStep) {
            if (calculationThread)
                calculationThread->join();
            calculationThread = std::make_unique<std::thread>(&Universe::update, &universe, timeFactor);
        }


        window.clear(sf::Color::Black);

        if (showTimeFactorMessage) {
            if (std::abs(timeFactor - 1) < 0.05) {
                showTimeFactorMessage = false;
            } else {
                window.setView(defaultView);
                timeFactorMessage.setString("Time factor: " + std::to_string(timeFactor));
                const sf::FloatRect& viewport = defaultView.getViewport();
                timeFactorMessage.setPosition({viewport.left, viewport.top});
                window.draw(timeFactorMessage);
                window.setView(view);
            }
        }

        universe.draw(window);

        window.display();
    }

    if (calculationThread) {
        calculationThread->join();
    }

    return 0;
}
