#include<iostream>
#include"nlohmann/json.hpp"

using json = nlohmann::json;

enum UpgradeCrystal{
    NO_Crystal,
    Rubat,
    Damind,
    Eralam,
    Sapith,
    Nextor,
    Opila,
    Jenruax,
    Phond,
    Luxum,
    Firkrann,
    Bondar,
    Sigil,
    Upari,
    Solari,
    Krayt
};

class Crystal{
    UpgradeCrystal cur;
    std::string crystal_stat_choice;
    public:
        Crystal();
        void updateCrystal(int select);
        void setStat(int choice);
        std::string curString();
        void printStats(json crystal_data);
        void printLocations(json crystal_data);
        int getVal();
    
    private:
        std::map<int, std::string> upgrade_strings = {
            {0, "No Crystal"},
            {1, "Rubat"},
            {2, "Damind"},
            {3, "Eralam"},
            {4, "Sapith"},
            {5, "Nextor"},
            {6, "Opila"},
            {7, "Jenruax"},
            {8, "Phond"},
            {9, "Luxum"},
            {10, "Firkrann"},
            {11, "Bondar"},
            {12, "Sigil"},
            {13, "Upari"},
            {14, "Solari"},
            {15, "Krayt Dragon Pearl"},
        };
};