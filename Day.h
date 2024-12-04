#pragma once

// Classe abstraite pour un jour
class Day {
public:
    std::string _name;
protected:
    std::vector<std::string> input;
public:
    explicit Day(const std::vector<std::string>& inputData, std::string name) : input(inputData), _name(name) {}
    virtual ~Day() = default;

    virtual void execPart1() = 0;
    virtual void execPart2() = 0;
};