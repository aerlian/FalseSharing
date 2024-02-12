cmake_minimum_required(VERSION 3.23)
project(FalseSharing)

set(CMAKE_CXX_STANDARD 23)

add_executable(FalseSharing main.cpp)

find_package(benchmark CONFIG REQUIRED)
target_link_libraries(FalseSharing benchmark::benchmark)

