#pragma once
#include "Day.h"
#include <iostream>

class Day3 : public Day {
public:
    explicit Day3(const std::vector<std::string>& inputData) : Day(inputData, "Day 3 - Mull It Over"){}

    void execPart1() override {
        std::cout << "Partie 1 - Nombre de lignes : " << input.size() << std::endl;
    }

    void execPart2() override {
        std::cout << "Partie 2 - Nombre de lignes : " << input.size() << std::endl;
    }
};
