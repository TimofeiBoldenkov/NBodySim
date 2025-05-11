#ifndef GUARD_Universe
#define GUARD_Universe

#include <vector>
#include "Planet.hpp"

class Universe {
public:
    Universe(double gravitationalConstant) : G(gravitationalConstant) { }

    void update(const sf::Time& time);
    
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

    const std::vector<Planet>& getPlanets() const {
        return planets;
    }
    void setPlanets(const std::vector<Planet>& planets) {
        this->planets = planets;
    }

    void addPlanet(const Planet& planet);

    sf::Vector2<double> forceOfGravity(std::vector<Planet>::const_iterator planet1, std::vector<Planet>::const_iterator planet2) const;
    sf::Vector2<double> forceOfGravity(std::vector<Planet>::size_type planet1Iindex, std::vector<Planet>::size_type planet2Index) const {
        return forceOfGravity(planets.begin() + planet1Iindex, planets.begin() + planet2Index);
    }

    sf::Vector2<double> acceleration(std::vector<Planet>::const_iterator iter) const;
    sf::Vector2<double> acceleration(int i) const {
        return acceleration(planets.begin() + i);
    }

private:
    std::vector<Planet> planets;
    double G;
};

#endif
