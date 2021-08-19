cmake_minimum_required(VERSION 3.16)
 
project(SpellCheckerTesting)

set(CMAKE_CXX_STANDARD 14)

# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

include_directories(/home/param/Desktop/Spell-Checker/src/)

set(SOURCES /home/param/Desktop/Spell-Checker/src/levenshtein.cpp /home/param/Desktop/Spell-Checker/src/levenshtein.h)

add_executable(SpellCheckerTesting main.cpp ${SOURCES})
target_link_libraries(SpellCheckerTesting ${GTEST_LIBRARIES} pthread)