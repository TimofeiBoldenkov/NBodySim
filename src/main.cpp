#include <unordered_map>
#include <iostream>
#include <thread>
#include <memory>
#include <Universe.hpp>
#include <utils.hpp>
#include <KeyboardHandler.hpp>

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
                throw std::invalid_argument("incorrect number of inputs");
            }
            double mass = std::stod(words[0]); // Throws std::invalid_argument if the input cannot be parsed as a double.

            std::cout << "Velocity of planet " << i + 1 << " (x y): ";
            std::getline(std::cin, line);
            if ((words = utils::split(line)).size() != 2) {
                throw std::invalid_argument("incorrect number of inputs");
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


    // Window size = display size / 1.3
    sf::VideoMode videoMode = sf::VideoMode::getDesktopMode();
    videoMode.height /= 1.3;
    videoMode.width /= 1.3;
    sf::RenderWindow window(videoMode, "Physical Simulation"); // Create a window
    // convenientView returns a view that includes all planets and fits within the given sf::VideoMode without distortion.
    sf::View view(utils::convenientView(universe, videoMode));
    view.zoom(2);
    window.setView(view);
    // defaultView is used when it is more convenient to place an object relative to the window rather than the universe.
    const sf::View defaultView = window.getDefaultView();
    
    // timeFactor defines how much faster (or slower) simulated time progresses compared to real time.
    float timeFactor = 1;
    sf::Font font;
    font.loadFromFile(PROJECT_SOURCE_DIR "/resources/Roboto-Regular.ttf"); // Load the font used for the message
    // Message about timeFactor. Shown if timeFactor is not equal to 1 or close to 1.
    sf::Text timeFactorMessage("Time factor: " + std::to_string(timeFactor), font, videoMode.height / 50);
    timeFactorMessage.setFillColor(sf::Color::White);

    const sf::Time kMinStep = sf::milliseconds(5); // Minimum interval between calculations
    KeyboardHandler keyboardHandler; // Object of a class that handles key press and release events
    // Calculations are performed in a separate thread.
    std::unique_ptr<std::thread> calculationThread;


    universe.restartClock(); // Start tracking time for the universe from now
    while (window.isOpen()) {
        sf::Event event;
        // The event handling loop
        while (window.pollEvent(event)) {
            // Zoom the view based on the mouse scroll delta
            if (event.type == sf::Event::MouseWheelScrolled) {
                view.zoom(std::pow(0.9, event.mouseWheelScroll.delta));
                window.setView(view);
            }

            // Key event
            if (event.type == sf::Event::KeyPressed || event.type == sf::Event::KeyReleased) {
                keyboardHandler.update(event); // Update keyboardHandler according to the event
            }

            // Close the window if the close button is pressed
            if (event.type == sf::Event::Closed)
                window.close();
        }
        
        // The following 4 if-conditions move the view according to the button pressed
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
        // Zoom out the view if the F-button (further) is pressed
        if (KeyInfo& keyInfo = keyboardHandler.keyInfo(sf::Keyboard::Key::F); keyInfo.pressed) {
            view.zoom(1 + keyInfo.clock.restart().asSeconds());
            window.setView(view);
        }
        // Zoom in the view if the C-button (closer) is pressed
        if (KeyInfo& keyInfo = keyboardHandler.keyInfo(sf::Keyboard::Key::C); keyInfo.pressed) {
            view.zoom(1 - keyInfo.clock.restart().asSeconds());
            window.setView(view);
        }
        // Speed up the simulation 
        if (KeyInfo& keyInfo = keyboardHandler.keyInfo(sf::Keyboard::Key::Z); keyInfo.pressed) {
            timeFactor /= 1 + keyInfo.clock.restart().asSeconds();
        }
        if (KeyInfo& keyInfo = keyboardHandler.keyInfo(sf::Keyboard::Key::X); keyInfo.pressed) {
            timeFactor *= 1 + keyInfo.clock.restart().asSeconds();
        }

        
        // If the minimum interval has elapsed
        if (universe.elapsedTime() > kMinStep) {
            // Wait for the previous calculation to finish
            if (calculationThread)
                calculationThread->join();
            // Start a new calculation
            calculationThread = std::make_unique<std::thread>(&Universe::update, &universe, timeFactor);
        }


        // Clear the window before drawing a new frame
        window.clear(sf::Color::Black);

        // Show the time factor only if it differs significantly from 1
        if (timeFactor < 0.95 || timeFactor > 1.05) {
            window.setView(defaultView); // Set the default view
            timeFactorMessage.setString("Time factor: " + std::to_string(timeFactor)); // Update the message
            const sf::FloatRect& viewport = defaultView.getViewport();
            timeFactorMessage.setPosition({viewport.left, viewport.top}); // Place the message in the top left corner
            window.draw(timeFactorMessage);
            window.setView(view); // Return to the standard view
        }

        universe.draw(window); // Draw all the planets

        window.display();
    }

    // Wait for the last calculation thread to finish
    if (calculationThread) {
        calculationThread->join();
    }

    return 0;
}
