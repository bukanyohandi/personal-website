cmake_minimum_required(VERSION 3.5)

project(CSC3050_P1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(CSC3050_P1 main.cpp phase1.cpp phase2.cpp labelTable.cpp tester.cpp)
