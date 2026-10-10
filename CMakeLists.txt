cmake_minimum_required(VERSION 3.10)
project(MmoRpgLab CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_executable(mmo_rpg main.cpp Health.cpp Armor.cpp Attack.cpp Unit.cpp GameField.cpp
    InfantryFactory.cpp ArcherFactory.cpp CavalryFactory.cpp)
