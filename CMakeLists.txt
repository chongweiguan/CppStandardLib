cmake_minimum_required(VERSION 3.10)  # Specify the minimum version of CMake required
project(MyProject VERSION 1.0 LANGUAGES CXX)  # Set the project name and the language used

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add executable
add_executable(my_program main.cpp)

# Add the source files to the executable
target_sources(my_program PRIVATE ${CONTAINERS_SOURCES} ${ALGORITHMS_SOURCES})

# Include directories if there are header files to consider
target_include_directories(my_program PRIVATE containers algorithms)