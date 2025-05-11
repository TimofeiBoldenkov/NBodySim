#ifndef GUARD_Vector2
#define GUARD_Vector2

#include <cmath>
#include <SFML/System/Vector2.hpp>

namespace Vector2Utils {

template<typename T>
T magnitude(const sf::Vector2<T>& vec)
{
    return std::sqrt(std::pow(vec.x, 2) + std::pow(vec.y, 2));
}

template<typename T>
sf::Vector2<T> directionalVector(T magnitude, const sf::Vector2<T>& direction)
{
    T len = Vector2Utils::magnitude(direction);
    return direction * (magnitude / len);
}

template<typename To, typename From>
sf::Vector2<To> convert(sf::Vector2<From> vec)
{
    return sf::Vector2<To>(vec.x, vec.y);
}

}

#endif
