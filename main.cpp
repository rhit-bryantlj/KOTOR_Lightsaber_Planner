#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include<list>

#include"nlohmann/json.hpp"
#include"Attributes.hpp"
#include"Lightsaber.hpp"

using json = nlohmann::json;

json crystal_data;

json getCrystalData() {
    std::ifstream crystal_file("Data/Crystals.json");
    json crystal_data = json::parse(crystal_file);
    return crystal_data;
}

Attributes initializeAttributes(){
    int attr[6];
    std::cout << "Input your Attributes:\nStrength: ";
    std::cin >> attr[0];
    std::cout << "Dexterity: ";
    std::cin >> attr[1];
    std::cout << "Constitution: ";
    std::cin >> attr[2];
    std::cout << "Intelligence: ";
    std::cin >> attr[3];
    std::cout << "Wisdom: ";
    std::cin >> attr[4];
    std::cout << "Charisma: ";
    std::cin >> attr[5];
    std::cout << "\n";

    return Attributes(attr[0], attr[1], attr[2], attr[3], attr[4], attr[5]);
}

void showCrystalDetails() {
    std::cout << crystal_data.dump(1) << std::endl;
}

int getUserCrystalOption(){
    int user_opt = -1;

    std::cout << "Select upgrade crystal - ";
    std::cout << "(0) No Crystal, (1) Rubat, (2) Damind\n(3) Eralam, (4) Sapith, (5) Nextor ";
    std::cout << "(6) Opila, (7) Jenruax\n(8) Phond, (9) Luxum, (10) Firkrann ";
    std::cout << "(11) Bondar, (12) Sigil\n(13) Upari, (14) Solari, (15) Krayt Dragon Pearl\n";
    std::cout << "(16) See Crystal Details\nSelect: ";

    while(user_opt < 0 || user_opt >= 16){
        std::cin >> user_opt;

        if(user_opt == 16){
            showCrystalDetails();
            continue;
        }else if(user_opt < 0 || user_opt > 16){
            std::cout << "Invalid input option. Please select again\n";
        }
    }
    return user_opt;
}

int getUserSaberColor(){
    int color_sel = -1;
    std::cout << "Select Saber Color Crystal - ";
    std::cout << "(0) Blue, (1) Green, (2) Red, (3) Yellow\n";
    std::cout << "(4) Purple (5) Heart of Guardian, (6) Mantle of Force\n";
    while(color_sel < 0 || color_sel > 6){
        std::cout << "Select: ";
        std::cin >> color_sel;
        std::cout << "\n";
        if(color_sel < 0 || color_sel > 6){
            std::cout << "Invalid input option. Please select again\n";
        }
    }
    return color_sel;
}

int getUserSaberType(){
    int saber_sel = -1;
    std::cout << "Select Saber Type - (0) Lightsaber, (1) Double-Bladed Lighsaber, (2) Short Lightsaber\n";
    while(saber_sel < 0 || saber_sel > 2){
        std::cout << "Select: ";
        std::cin >> saber_sel;
        
        if(saber_sel < 0 || saber_sel > 2){
            std::cout << "Invalid input option. Please select again\n";
        }
    }
    return saber_sel;
}

Lightsaber initializeLightsaber(){
    int saber_sel, color_sel, crystal1_sel, crystal2_sel;
    
    saber_sel = getUserSaberType();
    color_sel = getUserSaberColor();

    std::cout << "Crystal 1 Select: \n ";
    crystal1_sel = getUserCrystalOption();

    std::cout << "Crystal 2 Select: \n";
    crystal2_sel = getUserCrystalOption();
    std::cout << "\n";

    return Lightsaber(saber_sel, color_sel, crystal1_sel, crystal2_sel);
}

int userOptionLoop(){
    int user_opt;
    std::cout << "User Options:\n(0) Swap Crystal 1     (1) Swap Crystal 2     (2) Swap Color Crystal\n";
    std::cout << "(3) Change Lightsaber Style     (4) Update Attribute(s)     (5) Show Attributes\n";
    std::cout << "(6) Save Build (Future Implement)     (7) Load Build (Future Implement)     (8) Delete Build (Future Implement)\n";
    std::cout << "(9) Exit\nSelect: ";
    std::cin >> user_opt;
    std::cout << "\n\n";
    return user_opt;
}

int main() {
    std::cout << "Loading crystals...\n";
    crystal_data = getCrystalData();

    Attributes user_attr = initializeAttributes();

    Lightsaber user_saber = initializeLightsaber();

    int user_opt;
    int input;
    while(user_opt != 9){
        user_saber.showCurrentLightsaber(crystal_data);

        user_opt = userOptionLoop();
        switch(user_opt){
            case(0):
                std::cout << "Crystal 1 Select: \n ";
                input = getUserCrystalOption();
                user_saber.updateCrystal1(input);
                break;
            case(1):
                std::cout << "Crystal 2 Select: \n ";
                input = getUserCrystalOption();
                user_saber.updateCrystal2(input);
                break;
            case(2):
                input = getUserSaberColor();
                user_saber.updateColorCrystal(input);
                break;
            case(3):
                input = getUserSaberType();
                user_saber.updateLightsaberType(input);
                break;
            case(4):
                user_attr.updateAttribute();
                break;
            case(5):
                user_attr.showAttributes();
                break;
            case(6):
                std::cout << "user choice unsupported\n\n";
                break;
            case(7):
                std::cout << "user choice unsupported\n\n";
                break;
            case(8):
                std::cout << "user choice unsupported\n\n";
                break;
            case(9):
                break;
            default:
                std::cout << "user choice unsupported\n\n";
                break;
        }
    }
}