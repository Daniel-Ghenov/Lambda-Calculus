cmake_minimum_required(VERSION 3.10)
project(Substitution VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(Substitution Solution.cpp
        Terms/Abstraction.cpp
        Terms/Variable.cpp
        Terms/Application.cpp)