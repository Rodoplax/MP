cmake_minimum_required(VERSION 3.10.0)
project(MiFraud0 VERSION 0.1.0 LANGUAGES C CXX)

include_directories(include)

set(CMAKE_CXX_STANDART 14)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -pedantic")

add_executable(MiFraud0 src/main.cpp src/ArrayLocation.cpp src/Location.cpp src/VectorLocation.cpp)