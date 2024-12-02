#pragma once
#include "Day.h"
#include "Day1.h"
#include <iostream>

std::vector<std::vector<int>> cut_input_day2(std::vector<std::string>& input) {
    std::vector<std::vector<int>> res;
    std::for_each(input.begin(), input.end(), [&res](auto line) {
        std::vector<std::string> split_line = split(line, " ");
        std::vector<int> split_line_int;
        std::for_each(split_line.begin(), split_line.end(), [&split_line_int](auto v){
            split_line_int.push_back(std::stoi(v));
        });

        res.push_back(split_line_int);
    });
    return res;
}

class Day2 : public Day {
public:
    explicit Day2(const std::vector<std::string>& inputData) : Day(inputData, "Day 2 - Red-Nosed Reports"){}

    void execPart1() override {
        std::cout << "Partie 1 - Nombre de lignes : " << input.size() << std::endl;

        std::vector<std::vector<int>> reports = cut_input_day2(input);

        std::size_t num_safe = 0;
        std::for_each(reports.begin(), reports.end(), [&num_safe](std::vector<int> &report) {
            bool increase = report[0] < report[1];
            if (!increase) std::reverse(report.begin(), report.end());
            bool sorted = std::is_sorted(report.begin(), report.end());

            if (!sorted) return;

            bool adjacent_change = true;
            for (int i = 1; i < report.size(); i++) {
                int diff = report[i] - report[i-1];
                if (diff == 0 || diff < -3 || diff > 3) adjacent_change = false;
            }

            if (adjacent_change)
                num_safe++;
        });

        std::cout << "RESULT --> " << num_safe << std::endl;
    }

    void execPart2() override {
        std::cout << "Partie 2 - Nombre de lignes : " << input.size() << std::endl;

        std::vector<std::vector<int>> reports = cut_input_day2(input);

        std::size_t num_safe = 0;
        std::for_each(reports.begin(), reports.end(), [&num_safe](std::vector<int> &report) {
            
            bool safe = false;
            for (int dampener_index = 0; dampener_index < report.size() && !safe; dampener_index++) {

                std::vector<int> dampener_vector = report;
                dampener_vector.erase(dampener_vector.begin() + dampener_index);

                bool increase = dampener_vector[0] < dampener_vector[1];
                if (!increase) std::reverse(dampener_vector.begin(), dampener_vector.end());
                bool sorted = std::is_sorted(dampener_vector.begin(), dampener_vector.end());

                bool adjacent_change = true;
                for (int i = 1; i < dampener_vector.size(); i++) {
                    int diff = dampener_vector[i] - dampener_vector[i-1];
                    if (diff == 0 || diff < -3 || diff > 3) adjacent_change = false;
                }

                if (adjacent_change && sorted)
                    safe = true;
            }

            if (safe) num_safe++;
        });

        std::cout << "RESULT --> " << num_safe << std::endl;
    }
};
