#pragma once
#include "Day.h"
#include <iostream>

class Day2 : public Day {
public:
    explicit Day2(const std::vector<std::string>& inputData) : Day(inputData, "Day0 - Test"){}

    void execPart1() override {
        std::cout << "Partie 1 - Nombre de lignes : " << input.size() << std::endl;
    }

    void execPart2() override {
        std::cout << "Partie 2 - Nombre de lignes : " << input.size() << std::endl;
    }
};
