OPTION(USE_SYSTEM_CATCH2 "Use system Catch2 if possible" ON)
find_package(Catch2 3.7 QUIET)
if (Catch2_FOUND AND USE_SYSTEM_CATCH2)
    message(STATUS "Using system Catch2")
else()
    message(STATUS "Fetching Catch2 from GitHub...")
    FetchContent_Declare(Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG v3.7.1
        GIT_SHALLOW ON
        EXCLUDE_FROM_ALL
        SYSTEM
    )
    FetchCOntent_MakeAvailable(Catch2)
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/tests)

add_executable(test test.cpp)
target_link_libraries(test PRIVATE simulation_lib sfml-graphics sfml-window sfml-system Catch2::Catch2WithMain)
add_test(NAME my_test COMMAND test)
