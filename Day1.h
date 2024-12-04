#pragma once
#include "Day.h"
#include <iostream>
#include <vector>

std::vector<std::string> split(std::string s, std::string delimiter) {
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    std::string token;
    std::vector<std::string> res;

    while ((pos_end = s.find(delimiter, pos_start)) != std::string::npos) {
        token = s.substr (pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        if (token.length() > 0)
            res.push_back (token);
    }

    res.push_back (s.substr (pos_start));
    return res;
}

std::pair<std::vector<int>, std::vector<int>> cut_input(std::vector<std::string>& input) {
    std::pair<std::vector<int>, std::vector<int>> res;
    std::for_each(input.begin(), input.end(), [&res](auto line) {
        std::vector<std::string> split_line = split(line, " ");

        res.first.push_back(std::stoi(split_line[0]));
        res.second.push_back(std::stoi(split_line[1]));
    });
    return res;
}

class Day1 : public Day {
public:
    explicit Day1(const std::vector<std::string>& inputData) : Day(inputData, "Day 1 - Historian Hysteria"){}

    void execPart1() override {
        std::cout << "Partie 1 - Nombre de lignes : " << input.size() << std::endl;

        auto cut = cut_input(input);
        std::vector<int> first_col = cut.first;
        std::vector<int> second_col = cut.second;

        std::sort(first_col.begin(), first_col.end(), [](auto a, auto b) {
            return a < b;
        });
        std::sort(second_col.begin(), second_col.end(), [](auto a, auto b) {
            return a < b;
        });

        std::size_t sum = 0;
        for(std::size_t i = 0; i < first_col.size(); i++)
        {
            int diff = first_col[i] - second_col[i];
            if (diff < 0) diff = -diff;
            sum += diff;
        };

        std::cout << "RESULT --> " << sum << std::endl;
    }

    void execPart2() override {
        std::cout << "Partie 2 - Nombre de lignes : " << input.size() << std::endl;

        auto cut = cut_input(input);
        std::vector<int> first_col = cut.first;
        std::vector<int> second_col = cut.second;

        std::size_t score = 0;
        std::for_each(first_col.begin(), first_col.end(), [&second_col, &score](auto &v) {
            std::size_t mul = 0;
            std::for_each(second_col.begin(), second_col.end(), [&mul, &v](auto &v2) {
                if (v == v2) mul++;
            });
            score += mul * v;
        });

        std::cout << "RESULT --> " << score << std::endl;
    }
};
