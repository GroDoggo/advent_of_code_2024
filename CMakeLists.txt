cmake_minimum_required(VERSION 3.0...3.28.3)
project(ADVENT_OF_CODE_2024)

file(GLOB PROJECT_CPP_FILES
    "main.cpp"
)
file(GLOB PROJECT_INCLUDE_FILES
    "Day.h"
    "Day0.h"
    "Day1.h"
    "Day2.h"
    "Day3.h"
)

add_executable( ADVENT_OF_CODE_2024
${PROJECT_CPP_FILES}
${PROJECT_INCLUDE_FILES}
)