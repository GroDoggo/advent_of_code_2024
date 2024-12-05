#pragma once
#include "Day.h"
#include <iostream>

std::pair<std::vector<std::vector<int>>, std::vector<std::pair<int, int>>> cut_input_day5(const std::vector<std::string> input)
{
    std::pair<std::vector<std::vector<int>>, std::vector<std::pair<int, int>>> res;

    bool finishRecordRules = false;

    std::for_each(input.begin(), input.end(), [&res, &finishRecordRules](auto line) {

        if (line.empty()) {
            finishRecordRules = true;
            return;
        }

        if (finishRecordRules) {
            std::vector<std::string> split_line = split(line, ",");
            std::vector<int> line_numbers;
            std::for_each(split_line.begin(), split_line.end(), [&line_numbers](auto n){
                line_numbers.push_back(std::stoi(n));
            });
            res.first.push_back(line_numbers);
        } else {
            std::vector<std::string> split_rule = split(line, "|");
            std::pair<int, int> rule(std::stoi(split_rule[0]), std::stoi(split_rule[1]));
            res.second.push_back(rule);
        }
    });

    return res;
}

bool checkRule(std::vector<int> page, std::pair<int, int> rule) {
    auto find_first = std::find(page.begin(), page.end(), rule.first);
    if (find_first == page.end()) return true;

    auto find_second = std::find(page.begin(), page.end(), rule.second);
    if (find_second == page.end()) return true;

    int distance = std::distance(find_first, find_second);
    return distance > 0;
}

class Day5 : public Day
{
public:
    explicit Day5(const std::vector<std::string> &inputData) : Day(inputData, "Day 5 - Print Queue") {}

    void execPart1() override
    {
        std::cout << "Partie 1 - Nombre de lignes : " << input.size() << std::endl;

        std::size_t sum = 0;

        std::pair<std::vector<std::vector<int>>, std::vector<std::pair<int, int>>> rule_and_pages = cut_input_day5(input);
        std::vector<std::vector<int>> pages = rule_and_pages.first;
        std::vector<std::pair<int,int>> rules = rule_and_pages.second;

        std::for_each(pages.begin(), pages.end(), [&rules, &sum](auto page) {
            bool all_rules_passed = true;
            std::for_each(rules.begin(), rules.end(), [&page, &all_rules_passed] (auto rule) {
                if (all_rules_passed) {
                    bool is_rule_passed = checkRule(page, rule);
                    if (!is_rule_passed) {
                    std::cout << "Rule (" << rule.first << "," << rule.second << ") did not pass ";
                    std::for_each(page.begin(), page.end(), [](auto p) { std::cout << p << ","; });
                    std::cout << std::endl;
                    all_rules_passed = false;
                    }
                }
            });
            if (all_rules_passed) {
                std::for_each(page.begin(), page.end(), [](auto p) { std::cout << p << ","; });
                std::cout << " pass all the rules. Adding (" << page[((int)(page.size()/2))] << ")" << std::endl;
                sum += page[((int)(page.size()/2))];
            }

        });

        std::cout << "RESULT --> " << sum << std::endl;
    }

    void execPart2() override
    {
        std::cout << "Partie 2 - Nombre de lignes : " << input.size() << std::endl;

        std::size_t sum = 0;

        std::pair<std::vector<std::vector<int>>, std::vector<std::pair<int, int>>> rule_and_pages = cut_input_day5(input);
        std::vector<std::vector<int>> pages = rule_and_pages.first;
        std::vector<std::pair<int,int>> rules = rule_and_pages.second;

        std::for_each(pages.begin(), pages.end(), [&rules, &sum](std::vector<int> page) {
            bool all_rules_passed = true;
            std::for_each(rules.begin(), rules.end(), [&page, &all_rules_passed] (auto rule) {
                if (all_rules_passed) {
                    bool is_rule_passed = checkRule(page, rule);
                    if (!is_rule_passed) {
                    std::cout << "Rule (" << rule.first << "," << rule.second << ") did not pass ";
                    std::for_each(page.begin(), page.end(), [](auto p) { std::cout << p << ","; });
                    std::cout << std::endl;
                    all_rules_passed = false;
                    }
                }
            });
            if (all_rules_passed) {
                std::for_each(page.begin(), page.end(), [](auto p) { std::cout << p << ","; });
                std::cout << " pass all the rules." << std::endl;
            } else {
                std::vector<int> corrected_page;
                while (!page.empty()) {
                    bool found = false;
                    for (int i = 0; i < page.size() && !found; i++) {
                        bool can_be_pushed = true;
                        //std::cout << "searching if " << page[i] << " can be pushed" << std::endl;
                        for (int r = 0; r < rules.size() && can_be_pushed; r++) {
                            if (rules[r].second == page[i]) {
                                //std::cout << "Found in rule (" << rules[r].first << " | " << rules[r].second << std::endl;
                                auto find_first = std::find(page.begin(), page.end(), rules[r].first);
                                if (find_first != page.end()) {
                                    //std::cout << "Can't be pushed because " << rules[r].first << " is in the list" << std::endl;
                                    can_be_pushed = false;
                                } else {
                                    //std::cout << rules[r].first << " is not in the list, " << page[i] << " can still be pushed" << std::endl;
                                }
                            }
                        }
                        if (can_be_pushed) {
                            //std::cout << page[i] << " passed all the rules and are pushed" << std::endl;
                            corrected_page.push_back(page[i]);
                            auto removed_number = std::remove(page.begin(), page.end(), page[i]);
                            page.erase(removed_number, page.end());
                            found = true;
                        }
                    }
                    assert(! (!found && !page.empty()));
                }
                std::cout << "Corrected : ";
                std::for_each(corrected_page.begin(), corrected_page.end(), [](auto p) { std::cout << p << ","; });
                std::cout << "Adding (" << corrected_page[((int)(corrected_page.size()/2))] << ")" << std::endl;
                sum += corrected_page[((int)(corrected_page.size()/2))];
            }

        });

        std::cout << "RESULT --> " << sum << std::endl;
    }
};
