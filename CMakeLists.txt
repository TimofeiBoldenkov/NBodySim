set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

cmake_minimum_required(VERSION 3.25)
project(CMakeSFMLProject LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)

OPTION(USE_SYSTEM_SFML "Use system Catch2 if possible" ON)
find_package(SFML 2.5 COMPONENTS system window graphics QUIET)
if (SFML_FOUND AND USE_SYSTEM_SFML)
    message(STATUS "Using system SFML")
else()
    message(STATUS "Fetching SFML from GitHub...")
    FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.5.1
        GIT_SHALLOW ON
        SYSTEM
    )
    FetchContent_MakeAvailable(SFML)

endif()

add_library(simulation_lib STATIC
    src/Planet.cpp
    src/Universe.cpp
    src/utils.cpp
    src/KeyboardHandler.cpp
)
target_link_libraries(simulation_lib PUBLIC sfml-graphics sfml-window sfml-system)
add_executable(simulation src/main.cpp)
target_link_libraries(simulation PRIVATE simulation_lib)
target_include_directories(simulation_lib PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_compile_features(simulation PRIVATE cxx_std_17)

add_subdirectory(tests)

add_compile_definitions(PROJECT_SOURCE_DIR="${CMAKE_SOURCE_DIR}")

if(WIN32)
    add_custom_command(
        TARGET simulation
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:simulation>
        VERBATIM)
endif()
