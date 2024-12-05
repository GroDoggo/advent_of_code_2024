#pragma once
#include "Day.h"
#include <iostream>

std::vector<std::vector<char>> cut_input_day4(const std::vector<std::string> input)
{
    std::vector<std::vector<char>> res;

    std::for_each(input.begin(), input.end(), [&res](auto line)
                  {

        std::vector<char> char_line;
        std::for_each(line.begin(), line.end(), [&char_line](auto c) {
            char_line.push_back(c);
        });

        res.push_back(char_line); });

    return res;
}

void printTab(const std::vector<std::vector<char>> input)
{
    std::for_each(input.begin(), input.end(), [](auto line)
                  {
        std::for_each(line.begin(), line.end(), [](auto c) {
            std::cout << c << " - ";
        });

        std::cout << std::endl; });
}

std::vector<std::pair<int, int>> tryFindCharAround(const std::vector<std::vector<char>> input, std::size_t line, std::size_t col, char find)
{

    std::vector<std::pair<int, int>> res;

    const std::size_t num_line = input.size();
    const std::size_t num_col = input[0].size();

    for (int i = -1; i <= 1; i++)
    {
        for (int j = -1; j <= 1; j++)
        {
            if (i != 0 || j != 0)
            {
                std::size_t check_line = line + i;
                std::size_t check_col = col + j;

                if (check_line >= 0 && check_line < num_line && check_col >= 0 && check_col < num_col)
                {
                    char check_char = input[check_line][check_col];
                    if (check_char == find)
                    {
                        res.push_back(std::pair<int, int>(i, j));
                    }
                }
            }
        }
    }

    return res;
}

class Day4 : public Day
{
public:
    explicit Day4(const std::vector<std::string> &inputData) : Day(inputData, "Day 4 - Ceres Search") {}

    void execPart1() override
    {
        std::cout << "Partie 1 - Nombre de lignes : " << input.size() << std::endl;

        std::size_t count = 0;

        std::vector<std::vector<char>> input_tab = cut_input_day4(input);

        const std::size_t num_line = input_tab.size();
        const std::size_t num_col = input_tab[0].size();

        for (std::size_t line = 0; line < num_line; line++)
        {
            for (std::size_t col = 0; col < num_col; col++)
            {
                // Try to find X
                if (input_tab[line][col] == 'X')
                {
                    std::vector<std::pair<int, int>> dir = tryFindCharAround(input_tab, line, col, 'M');

                    std::for_each(dir.begin(), dir.end(), [&input_tab, &line, &col, &count](auto pair)
                    {
                        const std::size_t num_line = input_tab.size();
                        const std::size_t num_col = input_tab[0].size();

                        const int max_line = line + pair.first * 3;
                        const int max_col = col + pair.second * 3;

                        if (max_line < 0 || max_line >= num_line || max_col < 0 || max_col >= num_col)
                            return;

                        if (input_tab[line + pair.first][col + pair.second] == 'M' &&
                            input_tab[line + pair.first * 2][col + pair.second * 2] == 'A' &&
                            input_tab[line + pair.first * 3][col + pair.second * 3] == 'S')
                        {

                            std::cout << "XMAS FOUND AT (" << line << "," << col << ") with dir (" << pair.first << "," << pair.second << ")" << std::endl;
                            count++;
                        } 
                    });
                }
            }
        }

        std::cout << "FOUND " << count << " XMAS" << std::endl;
    }

    void execPart2() override
    {
        std::cout << "Partie 2 - Nombre de lignes : " << input.size() << std::endl;

        std::size_t count = 0;

        std::vector<std::vector<char>> input_tab = cut_input_day4(input);

        const std::size_t num_line = input_tab.size();
        const std::size_t num_col = input_tab[0].size();

        for (std::size_t line = 0; line < num_line; line++)
        {
            for (std::size_t col = 0; col < num_col; col++)
            {
                // Try to find X
                if (input_tab[line][col] == 'A')
                {
                    std::vector<std::pair<int, int>> dir = tryFindCharAround(input_tab, line, col, 'M');

                    int x_found = 0;
                    std::for_each(dir.begin(), dir.end(), [&input_tab, &line, &col, &x_found](auto pair)
                    {   
                        if (pair.first == 0 || pair.second == 0) return;

                        const std::size_t num_line = input_tab.size();
                        const std::size_t num_col = input_tab[0].size();

                        const int reverse_line = line - pair.first;
                        const int reverse_col = col - pair.second;

                        if(reverse_line < 0 || reverse_line >= num_line || reverse_col < 0 || reverse_col >= num_col) return;

                        if (input_tab[line + pair.first][col + pair.second] == 'M' &&
                            input_tab[line - pair.first][col - pair.second] == 'S') 
                            x_found++;
                    });

                    if (x_found == 2){
                        std::cout << "X-MAS FOUND AT (" << line << "," << col << ")" << std::endl;
                        count++;
                    }
                }
            }
        }

        std::cout << "FOUND " << count << " X-MAS" << std::endl;
    }
};
