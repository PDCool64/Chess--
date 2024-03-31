# Specify the minimum version for CMake
cmake_minimum_required(VERSION 3.10)

# Project's name
project(Chess)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)

# Add all .cpp files in src/ to SOURCES
file(GLOB SOURCES "src/*.cpp")

# Append all .cpp files in src/MoveGeneration/ to SOURCES
file(GLOB MOVE_GENERATION_SOURCES "src/MoveGeneration/*.cpp")
list(APPEND SOURCES ${MOVE_GENERATION_SOURCES})

add_executable(${PROJECT_NAME} ${SOURCES})