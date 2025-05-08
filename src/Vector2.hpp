#ifndef GUARD_Vector2
#define GUARD_Vector2

#include <cmath>
#include <SFML/System/Vector2.hpp>

template<typename T>
float magnitude(const sf::Vector2<T>& vec)
{
    return std::sqrt(std::pow(vec.x, 2), std::pow(vec.y, 2));
}

#endif
