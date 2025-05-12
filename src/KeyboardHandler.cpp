#include "KeyboardHandler.hpp"
#include <iostream>

void KeyboardHandler::update(const sf::Event& event)
{
    if (event.type == sf::Event::KeyPressed) {
        KeyInfo& info = keys[event.key.code];
        info.clock.restart();
        info.pressed = true;
    } else if (event.type == sf::Event::KeyReleased) {
        KeyInfo& info = keys[event.key.code];
        info.pressed = false;
    }
}
