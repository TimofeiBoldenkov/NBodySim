#ifndef GUARD_utils
#define GUARD_utils

#include <vector>
#include <string>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Window/VideoMode.hpp>
#include "Universe.hpp"

// Contains several utility functions.
namespace utils {

// Splits an std::string by the space characters 
// and reterns an std::vector<std::string> of the resulting substrings
std::vector<std::string> split(const std::string& str);

// Returns true if the string contains only the space characters, false otherwise.
bool isSpace(std::string);

// Returns a sf::FloatRect representing a view that includes all planets in the given Universe
// and fits within the given sf::VideoMode without distortion.
// If the universe occupies no space, returns {{0, 0}, {videoMode.width, videoMode.height}}.
sf::FloatRect convenientView(const Universe& universe, const sf::VideoMode& videoMode);

}

#endif