#pragma once
#include "Day.h"
#include <iostream>
#include <vector>

class Day1 : public Day {
public:
    explicit Day1(const std::vector<std::string>& inputData) : Day(inputData, "Day0 - Test"){}

    void execPart1() override {
        std::cout << "Partie 1 - Nombre de lignes : " << input.size() << std::endl;
    }

    void execPart2() override {
        std::cout << "Partie 2 - Première ligne : " << (input.empty() ? "Aucune donnée" : input[0]) << std::endl;
    }
};
