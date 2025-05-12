#ifndef GUARD_utils
#define GUARD_utils

#include <vector>
#include <string>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Window/VideoMode.hpp>
#include "Universe.hpp"

namespace utils {

std::vector<std::string> split(const std::string& str);

bool isSpace(std::string);

sf::FloatRect convenientView(const Universe& universe, const sf::VideoMode& videoMode);

}

#endif