#ifndef GUARD_KeyboardHandler
#define GUARD_KeyboardHandler

#include <unordered_map>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>

class KeyInfo {
public:
    sf::Clock clock;
    bool pressed;
};

class KeyboardHandler {
public:
    void update(const sf::Event& event);

    KeyInfo& keyInfo(sf::Keyboard::Key key) {
        return keys[key];
    }
    const KeyInfo& keyInfo(sf::Keyboard::Key key) const {
        return keys[key];
    }

private:
    std::unordered_map<sf::Keyboard::Key, KeyInfo> keys;
};

#endif
