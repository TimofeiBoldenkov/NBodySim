#ifndef GUARD_Vector2
#define GUARD_Vector2

#include <cmath>
#include <SFML/System/Vector2.hpp>

// Contains several useful functions for working with sf::Vector2<T>.
namespace Vector2Utils {

// Returns the magnitude of the given sf::Vector2<T>.
template<typename T>
T magnitude(const sf::Vector2<T>& vec)
{
    return std::sqrt(std::pow(vec.x, 2) + std::pow(vec.y, 2));
}

// Returns an sf::Vector2<T> created from the given magnitude and direction, specified by an sf::Vector2<T>.
template<typename T>
sf::Vector2<T> directionalVector(T magnitude, const sf::Vector2<T>& direction)
{
    T len = Vector2Utils::magnitude(direction);
    return direction * (magnitude / len);
}

// Converts the given sf::Vector<From> to a sf::Vector<To>, if the conversion from From to To is available.
template<typename To, typename From>
sf::Vector2<To> convert(sf::Vector2<From> vec)
{
    return sf::Vector2<To>(vec.x, vec.y);
}

}

#endif
