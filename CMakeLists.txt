# Specify the minimum version for CMake
cmake_minimum_required(VERSION 3.10)

# Project's name
project(Chess)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)

file(GLOB SOURCES "src/*.cpp")
add_executable(${PROJECT_NAME} ${SOURCES})