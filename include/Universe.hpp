#ifndef GUARD_Universe
#define GUARD_Universe

#include <vector>
#include "Planet.hpp"

// Represents a universe.
// The universe contains several planets stored in a std::vector,
// a gravitational constant used in calculations,
// and an internal clock used to track time during computations.
// If a Planet in the universe is invalid (i.e., planet.isValid() == false), the Planet will not affect other planets.
class Universe {
public:
    // Creates an empty Universe with the specified gravitational constant.
    Universe(double gravitationalConstant) : G(gravitationalConstant) { }

    // Updates the Universe's state based on the planets' states, the gravitational forces between them
    // and the elapsed time since the last update() or restartClock() call, multiplied by a time factor (default is 1).
    void update(float timeFactor = 1);

    // Draws all the planets in the Universe.
    void draw(sf::RenderWindow& window) const;

    // Returns a reference to the Planet specified by its index.
    Planet& operator[](int i) {
        return planets[i];
    }
    // Returns a constant reference to the Planet specified by its index.
    const Planet& operator[](int i) const {
        return planets[i];
    }

    // Returns the number of the planets.
    std::vector<Planet>::size_type size() const {
        return planets.size();
    }

    // Returns a constant reference to the std::vector of the planets.
    const std::vector<Planet>& getPlanets() const {
        return planets;
    }
    // Sets the planets to the specified value.
    void setPlanets(const std::vector<Planet>& planets) {
        this->planets = planets;
    }

    // Adds a new Planet to the Universe.
    void addPlanet(const Planet& planet);

    // Returns the force of gravity between the two planets specified by their iterators.
    sf::Vector2<double> forceOfGravity(std::vector<Planet>::const_iterator planet1, std::vector<Planet>::const_iterator planet2) const;
    // Returns the force of gravity between the two planets specified by their indexes.
    sf::Vector2<double> forceOfGravity(std::vector<Planet>::size_type planet1Iindex, std::vector<Planet>::size_type planet2Index) const {
        return forceOfGravity(planets.begin() + planet1Iindex, planets.begin() + planet2Index);
    }

    // Returns the force acting on the Planet specified by its iterator since the last update() call
    sf::Vector2<double> totalForceOnPlanet(std::vector<Planet>::const_iterator) const;
    // Returns the force acting on the Planet specified by its iterator since the last update() call
    sf::Vector2<double> totalForceOnPlanet(std::vector<Planet>::size_type i) const {
        return totalForceOnPlanet(planets.begin() + i);
    }

    // Returns the elapsed time since the last update() or restartClock() call
    sf::Time elapsedTime() const {
        return clock.getElapsedTime();
    }

    // Restarts the Universe's internal clock
    void restartClock() {
        clock.restart();
    }

private:
    sf::Clock clock;

    std::vector<Planet> planets;
    double G;
};

#endif
