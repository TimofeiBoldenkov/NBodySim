#ifndef GUARD_KeyboardHandler
#define GUARD_KeyboardHandler

#include <unordered_map>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>

// Contains information about a key.
// Includes a clock that measures the time since the key was last pressed, released, or clock.restart() was called,
// and a boolean flag indicating whether the key is currently pressed.
struct KeyInfo {
    sf::Clock clock;
    bool pressed;
};

// Represents a keyboard.
// Contains a container where the key type is sf::Keyboard::Key, and the value type is KeyInfo.
class KeyboardHandler {
public:
    // Updates key states based on the given sf::Event.
    void update(const sf::Event& event);

    // Returns the KeyInfo of the specified sf::Keyboard::Key.
    KeyInfo& getKeyInfo(sf::Keyboard::Key key) {
        return keys[key];
    }
    // Returns the KeyInfo of the specified sf::Keyboard::Key.
    // Throws an std::out_of_range exception if the key is not found in the container.
    const KeyInfo& getKeyInfo(sf::Keyboard::Key key) const {
        return keys.at(key);
    }

private:
    std::unordered_map<sf::Keyboard::Key, KeyInfo> keys;
};

#endif
