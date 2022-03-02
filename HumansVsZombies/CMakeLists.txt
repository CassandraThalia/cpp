cmake_minimum_required(VERSION 3.20)
project(HumansVsZombies)

set(CMAKE_CXX_STANDARD 14)

add_executable(HumansVsZombies main.cpp City.cpp City.h Organism.cpp Organism.h Human.cpp Human.h GameSpecs.h Zombie.cpp Zombie.h)
