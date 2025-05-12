#include "KeyboardHandler.hpp"

void KeyboardHandler::update(const sf::Event& event)
{
    if (event.type == event.KeyPressed) {
        KeyInfo& info = keys[event.key.code];
        info.clock.restart();
        info.pressed = true;
    } else if (event.type == event.KeyReleased) {
        KeyInfo& info = keys[event.key.code];
        info.pressed = false;
    }
}
