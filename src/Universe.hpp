#ifndef GUARD_Universe
#define GUARD_Universe

#include <vector>
#include "Planet.hpp"

class Universe {
public:
    void move(sf::Time time);
    
    void draw(sf::RenderWindow& window) const;

    std::vector<Planet>::iterator begin() {
        return planets.begin();
    }
    std::vector<Planet>::const_iterator begin() const {
        return planets.begin();
    }

    std::vector<Planet>::iterator end() {
        return planets.end();
    }
    std::vector<Planet>::const_iterator end() const {
        return planets.end();
    }

    Planet& operator[](int i) {
        return planets[i];
    }
    const Planet& operator[](int i) const {
        return planets[i];
    }

    void addPlanet(Planet planet);

    sf::Vector2f acceleration(std::vector<Planet>::const_iterator iter) const;
    sf::Vector2f acceleration(int i) const {
        return acceleration(planets.begin() + i);
    }

private:
    std::vector<Planet> planets;
};

#endif
