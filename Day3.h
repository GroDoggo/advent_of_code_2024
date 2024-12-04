#pragma once
#include "Day.h"
#include <iostream>
#include <cassert>
#include <bits/stl_numeric.h>

const std::vector<char> allowed_char_in_mul = {'0', '1', '2', '3', '4',
                                               '5', '6', '7', '8', '9',
                                               ','};

std::vector<std::pair<int, int>> cut_input_day3(std::vector<std::string> &input)
{
    std::vector<std::pair<int, int>> res;

    std::for_each(input.begin(), input.end(), [&res](auto line)
                  {
        std::vector<std::string> split_mul = split(line, "mul(");

        std::for_each(split_mul.begin(), split_mul.end(), [&res] (std::string& mul_input) {
            std::vector<std::string> split_end_mul = split(mul_input, ")");
            if (split_end_mul.empty()) return;
            
            std::string mul_true_input = split_end_mul[0];

            if (mul_true_input.empty()) return;

            for (char& c : mul_true_input) {
                auto found = std::find(allowed_char_in_mul.begin(), allowed_char_in_mul.end(), c);
                if (found == allowed_char_in_mul.end()) return;
            }

            int num_del = std::count(mul_true_input.begin(), mul_true_input.end(), ',');
            if (num_del != 1) return;
            std::size_t delimiter_index = mul_true_input.find(',');

            std::string first_part_str = mul_true_input.substr(0, delimiter_index);
            std::string second_part_str = mul_true_input.substr(delimiter_index + 1);

            if (first_part_str.empty() || second_part_str.empty()) return;

            std::cout << first_part_str << " - " << second_part_str << std::endl;

            int first_part = std::stoi(first_part_str);
            int second_part = std::stoi(second_part_str);
                
            res.push_back(std::pair<int, int>(first_part, second_part));
        
        }); });
    return res;
}

std::pair<int, int> get_mul_content(std::string mul_content_str)
{
    std::vector<std::string> split_end_mul = split(mul_content_str, ")");
    if (split_end_mul.empty())
        return std::pair<int, int>(-1, -1);

    std::string mul_true_input = split_end_mul[0];

    if (mul_true_input.empty())
        return std::pair<int, int>(-1, -1);

    for (char &c : mul_true_input)
    {
        auto found = std::find(allowed_char_in_mul.begin(), allowed_char_in_mul.end(), c);
        if (found == allowed_char_in_mul.end())
            return std::pair<int, int>(-1, -1);
    }

    int num_del = std::count(mul_true_input.begin(), mul_true_input.end(), ',');
    if (num_del != 1)
        return std::pair<int, int>(-1, -1);
    std::size_t delimiter_index = mul_true_input.find(',');

    std::string first_part_str = mul_true_input.substr(0, delimiter_index);
    std::string second_part_str = mul_true_input.substr(delimiter_index + 1);

    if (first_part_str.empty() || second_part_str.empty())
        return std::pair<int, int>(-1, -1);

    std::cout << first_part_str << " - " << second_part_str << std::endl;

    int first_part = std::stoi(first_part_str);
    int second_part = std::stoi(second_part_str);

    return std::pair<int, int>(first_part, second_part);
}

class Day3 : public Day
{
public:
    explicit Day3(const std::vector<std::string> &inputData) : Day(inputData, "Day 3 - Mull It Over") {}

    void execPart1() override
    {
        std::cout << "Partie 1 - Nombre de lignes : " << input.size() << std::endl;
        std::vector<std::pair<int, int>> mul_list = cut_input_day3(input);

        std::size_t sum = 0;
        std::for_each(mul_list.begin(), mul_list.end(), [&sum](std::pair<int, int> &pair)
                      { sum += pair.first * pair.second; });

        std::cout << "RESULT --> " << sum << std::endl;
    }

    void execPart2() override
    {
        std::cout << "Partie 2 - Nombre de lignes : " << input.size() << std::endl;

        bool mul_enable = true;
        std::size_t sum = 0;
        std::for_each(input.begin(), input.end(), [&mul_enable, &sum](std::string line) {
            
            for (std::size_t index = 0; index < line.size(); index++) {
            
                // DO
                if (index + 4 < line.size()) {
                    std::string substr_do = line.substr(index, 4);
                    if (!substr_do.compare("do()")) mul_enable = true;
                }

                // DONT
                if (index + 7 < line.size()) {
                    std::string substr_dont = line.substr(index, 7);
                    if (!substr_dont.compare("don't()")) mul_enable = false;
                }

                // MUL
                if (mul_enable && index + 5 < line.size()) {
                    std::string substr_mul = line.substr(index, 4);
                    if (!substr_mul.compare("mul(")) {
                        std::string substr_mul_content = line.substr(index + 4);

                        std::pair<int, int> res = get_mul_content(substr_mul_content);

                        if (res.first != -1) {
                            sum += res.first * res.second;
                        }
                    }
                }
            }
        });

        std::cout << "RESULT --> " << sum << std::endl;
    }
};
