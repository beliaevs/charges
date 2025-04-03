cmake_minimum_required(VERSION 3.15)
project(charges)
set(CMAKE_CXX_STANDARD 17)
add_executable(charges main.cpp EquilibriumFinder.cpp EquilibriumFinder.h chargesystem.cpp chargesystem.h Vector3.h coulomb.h)

