# NBodySim – A Simple N-Body Problem Simulator
__NBodySim__ is a simple, cross-platform and multithreaded simulation of the _n-body problem_, written in C++. It uses [__SFML__](https://www.sfml-dev.org/) for visualization, [__Catch2__](https://github.com/catchorg/Catch2) for testing and the [_Euler method_](https://en.wikipedia.org/wiki/Euler_method) for numerical approximation.
## Interaction with the Program
After launching the program, it will ask each planet's mass, velocity and position. To stop adding new planets, leave the input blank. If you enter invalid data, the program will report the mistake. 

Once you've added all the planets you want, the simulation will begin. A new window will open, showing a view that includes all the planets you've added. The program provides several options for controlling the view:
* Press __X__ to speed up
* Press __Z__ to slow down
* Press __C__ or scroll the mouse wheel up to zoom in
* Press __F__ or scroll the mouse wheel down to zoom out
* Use the arrow keys to move the view

Example input files can be found in the `examples` directory.
## Building
The project uses CMake for building. To build the project into the `build` directory on your system, run the following commands from the project's root directory:
```
cmake -S . -B build
cmake --build build
```
After building, the executable files can be found in `build/bin`.

CMake will attempt to find the __SFML__ and __Catch2__ libraries on your system using `find_package`; if the search fails, it will automatically fetch the libraries from GitHub. 

You can also force CMake to fetch the libraries from GitHub, even if they are available on your system, by setting `USE_SYSTEM_SFML` and `USE_SYSTEM_CATCH2` to `FALSE`. In that case, the build process would look like this:
```
cmake -S . -B build -DUSE_SYSTEM_SFML=FALSE -DUSE_SYSTEM_CATCH2=FALSE
cmake --build build
```
## Program's Structure
The `Planet` class represents a planet. It has properties such as mass, velocity, position and shape. All the numerical values are stored as `double`s. The shape is used only for drawing the planet; physically, all the planets are point masses - i.e., objects that have mass but no size. A planet can be moved according to its current velocity and the elapsed time by the `update` method and drawn to a given window by the `draw` method. A planet is considered invalid if its mass, velocity, or position is a non-finite value or if the mass equals to zero. The `draw` method does not draw an invalid planet.

The `Universe` class represents a universe. It stores planets in a `std::vector` and contains an internal clock for tracking time, as well as the gravitational constant used in physical calculations. The class itself does not contain any window for drawing; it only maintains physical and appearance-related properties of its objects, and convenient methods for drawing to a given `SFML` window. The gravitational constant is set by the user when creating a `Universe`. The class has the `update` method that recalculates each planet's parameters (e.g. position and velocity) based on their previous state, the gravitational forces between the planets, and the time elapsed since the last `update` call. All planets can be drawn to a given window by the `draw` method. If a universe contains an invalid planet, the planet will not affect other planets in the universe. In other words, an invalid planet is "thrown out" of the system. Although it is not possible according to classical mechanics, a planet still may have a negative mass.

The program uses an auxiliary `KeyboardHandler` class that contains information about keys - whether a key is pressed or not, and how much time has elapsed since the key was last updated. Key information can be updated using the `update` method based on a given `sf::Event` and retrieved using the `getKeyInfo` method based on a given key code.

Physical calculations are performed in a separate thread. They are executed whenever a minimum time interval has elapsed, which is 5 milliseconds by default. The [_Euler method_](https://en.wikipedia.org/wiki/Euler_method) is used for approximation.

The program uses unit tests written with the [__Catch2__](https://github.com/catchorg/Catch2) library. The tests are located in the `tests` directory.
