cmake_minimum_required(VERSION 3.5)

project(simulator LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(simulator main.cpp labeltable.cpp phase1.cpp phase2.cpp checkpoints.cpp)
