#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <functional>

#include "Day.h"
#include "Day0.h"
#include "Day1.h"
#include "Day2.h"
#include "Day3.h"
#include "Day4.h"

#define INPUTS_FOLDER_PATH "../inputs/"

// Classe pour lire un fichier d'entrée
class FileReader {
public:
    static std::vector<std::string> readInputFile(const std::string& filename) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            throw std::runtime_error("Erreur : Impossible d'ouvrir le fichier " + filename);
        }

        std::vector<std::string> lines;
        std::string line;
        while (std::getline(file, line)) {
            lines.push_back(line);
        }
        return lines;
    }
};

class DayManager {
private:
    std::unordered_map<int, std::function<std::unique_ptr<Day>(const std::vector<std::string>&)>> dayRegistry;

public:
    DayManager() {
        dayRegistry[0] = [](const std::vector<std::string>& input) { return std::make_unique<Day0>(input); };
        dayRegistry[1] = [](const std::vector<std::string>& input) { return std::make_unique<Day1>(input); };
        dayRegistry[2] = [](const std::vector<std::string>& input) { return std::make_unique<Day2>(input); };
        dayRegistry[3] = [](const std::vector<std::string>& input) { return std::make_unique<Day3>(input); };
        dayRegistry[4] = [](const std::vector<std::string>& input) { return std::make_unique<Day4>(input); };
        // Ajouter d'autres jours ici
    }

    void runDay(int day, int part, bool use_example) {
        auto it = dayRegistry.find(day);
        if (it == dayRegistry.end()) {
            std::cerr << "Erreur : Jour " << day << " non implémenté." << std::endl;
            return;
        }

        try {
            std::string filename;
            if (use_example)
                filename = std::string(INPUTS_FOLDER_PATH) + "input_day" + std::to_string(day) + "_example.txt";
            else
                filename = std::string(INPUTS_FOLDER_PATH) + "input_day" + std::to_string(day) + ".txt";
            std::vector<std::string> input = FileReader::readInputFile(filename);

            auto dayInstance = it->second(input);

            if (part == 1) {
                dayInstance->execPart1();
            } else if (part == 2) {
                dayInstance->execPart2();
            } else {
                std::cerr << "Erreur : Partie " << part << " invalide." << std::endl;
            }
        } catch (const std::exception& e) {
            std::cerr << e.what() << std::endl;
        }
    }

    void listAvailableDays() {
        std::cout << "Jours disponibles : \n";
        for (const auto& entry : dayRegistry) {
            auto instance = entry.second(std::vector<std::string>());
            std::string instanceName = instance->_name;

            std::cout << entry.first << " : " << instanceName << "\n";
        }
        std::cout << std::endl;
    }
};

// Fonction principale
int main() {

    DayManager manager;
    manager.listAvailableDays();

    int day, part;
    bool use_example;
    std::cout << "Entrez le numéro du jour : ";
    std::cin >> day;
    std::cout << "Entrez le numéro de la partie (1 ou 2) : ";
    std::cin >> part;
    std::cout << "Utiliser l'input d'exemple? ";
    std::cin >> use_example;

    manager.runDay(day, part, use_example);

    return 0;
}
