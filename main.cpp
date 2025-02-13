#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include<list>

#include"nlohmann/json.hpp"
#include"Lightsaber.hpp"

using json = nlohmann::json;

json crystal_data;

/*
uint _64 = [dead space=7][L2 up 2 = 4][L2 up 1 = 4][L2 color = 3][L2 saber type=2][L2 flag=1]
                [L1 up 2=4][L1 up 1=4][L1 color=3][saber typ=2][char=5][wis=5][int=5][dex=5][con=5][str=5]
*/

const uint64_t STR_MASK = 0x1F;
const uint64_t DEX_MASk = 0x3E0;
const uint64_t CON_MASK = 0x7C00;
const uint64_t INT_MASK = 0xF8000;
const uint64_t WIS_MASK = 0x1F00000;
const uint64_t CHAR_MASK = 0x3E000000;
const uint64_t S1_TYPE_MASK = 0xC0000000;
const uint64_t S1_COLOR_MASK = 0x700000000;
const uint64_t S1_CRYSTAL_1_MASK = 0x7800000000;
const uint64_t S1_CRYSTAL_2_MASK = 0x78000000000;
const uint64_t S2_FLAG = 0x80000000000;
const uint64_t S2_TYPE_MASK = 0x300000000000;
const uint64_t S2_COLOR_MASK = 0x1C00000000000;
const uint64_t S2_CRYSTAL_1_MASK = 0x1E000000000000;
const uint64_t S2_CRYSTAL_2_MASK = 0x1E0000000000000;

/* Tests
Check out memory and using a deconstructor/ class destructor once its implemented just creating a new saber*/

json getCrystalData() {
    std::ifstream crystal_file("Data/Crystals.json");
    json crystal_data = json::parse(crystal_file);
    crystal_file.close();
    return crystal_data;
}

int getUserInt(){
    int temp;
    while(!(std::cin >> temp)){
        std::cout << "Not integer input\nEnter:";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    return temp;
}

bool attributeCheck(int attr[6]){
    int sum = 0;
    for(int i = 0; i < 6; i++){
        if(attr[i] < 8 || attr[i] > 23){
            std::cout << "Attribute out of possible bounds. Enter again\n";
            return false;
        }
        sum += attr[i];
    }
    // Make this more of a complete check for the max possible stat points
    // Considering the Point Cost restriction of Character Creation.
    if(sum > 83){ 
        std::cout << "User Attribute sum higher than possible max. Enter again\n";
        return false;
    }
    return true;
}

Attributes initializeAttributes(){
    int attr[6];
    bool fair_attr = false;
    while(!fair_attr){
        std::cout << "Input your Attributes:\nStrength: ";
        attr[0] = getUserInt();
        std::cout << "Dexterity: ";
        attr[1] = getUserInt();
        std::cout << "Constitution: ";
        attr[2] = getUserInt();
        std::cout << "Intelligence: ";
        attr[3] = getUserInt();
        std::cout << "Wisdom: ";
        attr[4] = getUserInt();
        std::cout << "Charisma: ";
        attr[5] = getUserInt();
        std::cout << "\n";
        fair_attr = attributeCheck(attr);
    }

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
        user_opt = getUserInt();

        if(user_opt == 16){
            showCrystalDetails();
            std::cout << "\nSelect upgrade crystal - ";
            std::cout << "(0) No Crystal, (1) Rubat, (2) Damind\n(3) Eralam, (4) Sapith, (5) Nextor ";
            std::cout << "(6) Opila, (7) Jenruax\n(8) Phond, (9) Luxum, (10) Firkrann ";
            std::cout << "(11) Bondar, (12) Sigil\n(13) Upari, (14) Solari, (15) Krayt Dragon Pearl\n";
            std::cout << "(16) See Crystal Details\nSelect: ";
            continue;
        }else if(user_opt < 0 || user_opt > 16){
            std::cout << "Invalid input option. Please select again\n";
        }
    }
    std::cout << "\n";
    return user_opt;
}

int getUserSaberColor(){
    int color_sel = -1;
    std::cout << "Select Saber Color Crystal - ";
    std::cout << "(0) Blue, (1) Green, (2) Red, (3) Yellow\n";
    std::cout << "(4) Purple (5) Heart of Guardian, (6) Mantle of Force\n";
    while(color_sel < 0 || color_sel > 6){
        std::cout << "Select: ";
        color_sel = getUserInt();
        std::cout << "\n";
        if(color_sel < 0 || color_sel > 6){
            std::cout << "Invalid input option. Please select again\n";
        }
    }
    return color_sel;
}

int getUserSaberType(bool equipping_second){
    int saber_sel = -1;
    if(!equipping_second)
        std::cout << "Select Saber Type - (0) Lightsaber, (1) Double-Bladed Lighsaber, (2) Short Lightsaber\n";
    else{
        std::cout << "Select Saber Type - (0) Lightsaber,  (2) Short-Lightsaber\n";
    }
    while(saber_sel < 0 || saber_sel > 2){
        std::cout << "Select: ";
        saber_sel = getUserInt();
        if(saber_sel < 0 || saber_sel > 2){
            std::cout << "Invalid input option. Please select again\n";
        }
        if(equipping_second && saber_sel == 1){
            std::cout << "Invalid input option. Please select again\n";
            saber_sel = -1;
        }
    }
    return saber_sel;
}

Lightsaber initializeLightsaber(bool equipping_second){
    int saber_sel, color_sel, crystal1_sel, crystal2_sel;
    
    saber_sel = getUserSaberType(equipping_second);
    color_sel = getUserSaberColor();

    std::cout << "Crystal 1 Select: \n ";
    crystal1_sel = getUserCrystalOption();

    std::cout << "Crystal 2 Select: \n";
    crystal2_sel = getUserCrystalOption();
    std::cout << "\n";

    return Lightsaber(saber_sel, color_sel, crystal1_sel, crystal2_sel);
}

void show_saved_builds(){
    std::ifstream save_file("Data/saves.json");
    json saves_json = json::parse(save_file);
    std::cout << "Current Saves:\n" << saves_json.dump(1) << "\n\n";
    save_file.close();
}

void save_cur_build(Attributes user_attr, Lightsaber user_saber, bool second_equipped, Lightsaber saber2){
    uint64_t build = 0;


    //if second saber equipped, put in at the front end of 
    // the build num in same order with a flag to check
    // first in the loading function
    if(second_equipped){
        build += saber2.crystal_2.getVal();
        build = build << 4;
        build += saber2.crystal_1.getVal();
        build = build << 3;
        build += saber2.getColorVal();
        build = build << 2;
        build += saber2.getTypeVal();
        build = build << 1;
        build += 1; // const 1 to indicate that there is a second saber to load
        build = build << 4;
    }

    build += user_saber.crystal_2.getVal();

    build = build << 4;
    build += user_saber.crystal_1.getVal();

    build = build << 3;
    build += user_saber.getColorVal();

    build = build << 2;
    build += user_saber.getTypeVal();

    build = build << 5;
    build+= user_attr.getChar();

    build = build << 5;
    build += user_attr.getWis();
    
    build = build << 5;
    build += user_attr.getInt();

    build = build << 5;
    build += user_attr.getCon();

    build = build << 5;
    build += user_attr.getDex();

    build = build << 5;
    build += user_attr.getStr();

    std::string build_name;
    std::cout << "Provide a name for the build to save:\n";
    std::cin >> build_name;
    std::cout << "\n";

    std::ifstream save_file("Data/saves.json");
    json saves_json = json::parse(save_file);
    save_file.close();

    int id = saves_json.size();

    saves_json[std::to_string(id)] = {{"name", build_name}, {"value", build}};

    std::ofstream save_write("Data/saves.json");
    save_write << saves_json.dump(1);
    save_write.close();
}

void load_build(Attributes& user_attr, Lightsaber& user_saber, Lightsaber& saber2, bool& second_equipped){
    std::ifstream save_file("Data/saves.json");
    json saves_json = json::parse(save_file);
    save_file.close();
    if(saves_json.size() == NULL){
        std::cout << "No current saves available.\n\n";
        return;
    }
    std::cout << "Current saves: \n\n";
    std::cout << saves_json.dump(1) << "\n";

    int id;
    std::cout << "Load which build? (Provide the int id)\n";
    while(!(std::cin >> id)){
        std::cout << "Not integer: Select: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    int size = saves_json.size();
    if(id > size || id < 0){
        std::cout << "Given id is outside of range. Request denied\n\n";
        return;
    }

    int str, dex, con, wis, intel, charis;

    uint64_t build = saves_json[std::to_string(id)]["value"];
    // std::cout << build << "\n";

    str = (STR_MASK & build);
    dex = (DEX_MASk & build) >> 5;
    con = (CON_MASK & build) >> 10;
    intel = (INT_MASK & build) >> 15;
    wis = (WIS_MASK & build) >> 20; 
    charis = (CHAR_MASK & build) >> 25;

    user_attr.setAttributes(str,dex,con,intel,wis,charis);

    user_saber.updateLightsaberType((S1_TYPE_MASK & build) >> 30);
    user_saber.updateColorCrystal((S1_COLOR_MASK & build) >> 32);
    user_saber.updateCrystal1((S1_CRYSTAL_1_MASK & build) >> 35);
    user_saber.updateCrystal2((S1_CRYSTAL_2_MASK & build) >> 39);

    if((S2_FLAG & build) >> 43){
        second_equipped = true;
        saber2.updateLightsaberType((S2_TYPE_MASK & build) >> 44);
        saber2.updateColorCrystal((S2_COLOR_MASK & build) >> 46);
        saber2.updateCrystal1((S2_CRYSTAL_1_MASK & build) >> 49);
        saber2.updateCrystal2((S2_CRYSTAL_2_MASK & build) >> 53);
    } else{
        second_equipped = false;
    }
    
    std::cout << "\nCurrent Attributes\n" << "---------------------------------\n\n";
    user_attr.showAttributes();
}

void delete_build(){
    std::ifstream save_file("Data/saves.json");
    json saves_json = json::parse(save_file);
    save_file.close();
    if(saves_json.size() == NULL){
        std::cout << "No current saves available.\n\n";
        return;
    }
    std::cout << "Current saves: \n\n";
    std::cout << saves_json.dump(1) << "\n";

    int id;
    std::cout << "Delete which build? (Provide the int id)\n";
    while(!(std::cin >> id)){
        std::cout << "Not integer: Select: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    
    int size = saves_json.size();
    if(id > size || id < 0){
        std::cout << "Given id is outside of range. Request denied\n\n";
        return;
    }

    saves_json.erase(std::to_string(id));
    while(id < size - 1){
        saves_json[std::to_string(id)] = saves_json[std::to_string(id + 1)];
        id++;
    }
    saves_json.erase(std::to_string(id));
    std::ofstream save_write("Data/saves.json");
    save_write << saves_json;
    save_write.close();
    std::cout << "Request completed.\n\n";
}

int userOptionLoop(bool second_equipped){
    int user_opt;
    std::cout << "User Options:\n(0) Swap Crystal 1     (1) Swap Crystal 2     (2) Swap Color Crystal\n";
    std::cout << "(3) Change Lightsaber Style     (4) Update Attribute(s)     (5) Show Attributes\n";
    std::cout << "(6) Show Current Crystal Locations    (7) Save Build      (8) Load Build\n";
    std::cout << "(9) Delete Build    (10) Show Saved Builds     ";
    if(!second_equipped){
        std::cout << "(11) Equip Second Lightsaber\n";
    } else{
        std::cout << "(11) Unequip Second Lightsaber\n";
    }
    std::cout << "(12) Exit\nSelect: ";
    user_opt = getUserInt();
    std::cout << "---------------------------------\n\n";
    return user_opt;
}

int main() {
    std::cout << "Loading crystals...\n";
    crystal_data = getCrystalData();

    Attributes user_attr = initializeAttributes();

    Lightsaber user_saber_1 = initializeLightsaber(false);

    // Initialize to an empty lightsaber object
    Lightsaber user_saber_2 = Lightsaber();

    int user_opt;
    int input;
    bool second_equipped = false;
    while(user_opt != 12){
        // create a new function to show these side by side and not multiply the attribute bonus outputs
        user_saber_1.showCurrentLightsaber(crystal_data, user_attr);
        if(second_equipped){
            user_saber_2.showCurrentLightsaber(crystal_data, user_attr);
        }
    
        user_opt = userOptionLoop(second_equipped);
        // make each update request have the option to upgrade lightsaber 1 or 2, color, etc
        switch(user_opt){
            case(0):
                if(second_equipped){
                    std::cout << "Update which saber? 1 or 2\nSelect: ";
                    input = getUserInt();
                    if(input == 1){
                        std::cout << "Crystal 1 Select: \n";
                        input = getUserCrystalOption();
                        std::cout << "\n";
                        user_saber_1.updateCrystal1(input);
                    } else if(input == 2){
                        std::cout<<"Crystal 1 Select: \n";
                        input = getUserCrystalOption();
                        std::cout << "\n";
                        user_saber_2.updateCrystal1(input);    
                    } else{
                        std::cout << "Invalid option. Cancelling request\n\n";
                    }
                } else{
                    std::cout << "Crystal 1 Select: \n ";
                    input = getUserCrystalOption();
                    user_saber_1.updateCrystal1(input);
                }
                break;
            case(1):
                if(second_equipped){
                    std::cout << "Update which saber? 1 or 2\nSelect: ";
                    input = getUserInt();
                    if(input == 1){
                        std::cout << "Crystal 2 Select: \n";
                        input = getUserCrystalOption();
                        std::cout << "\n";
                        user_saber_1.updateCrystal2(input);
                    } else if(input == 2){
                        std::cout<<"Crystal 2 Select: \n";
                        input = getUserCrystalOption();
                        std::cout << "\n";
                        user_saber_2.updateCrystal2(input);    
                    } else{
                        std::cout << "Invalid option. Cancelling request\n\n";
                    }
                } else{
                    std::cout << "Crystal 2 Select: \n ";
                    input = getUserCrystalOption();
                    user_saber_1.updateCrystal2(input);
                }
                break;
            case(2):
                if(second_equipped){
                    std::cout << "Update which saber? 1 or 2\nSelect: ";
                    input = getUserInt();
                    if(input == 1){
                        input = getUserSaberColor();
                        user_saber_1.updateColorCrystal(input);
                    } else if(input == 2){
                        input = getUserSaberColor();
                        user_saber_2.updateColorCrystal(input);
                    } else{
                        std::cout << "Invalid option. Cancelling request\n\n";
                    }
                } else{
                    input = getUserSaberColor();
                    user_saber_1.updateColorCrystal(input);
                }
                break;
            case(3):
                if(second_equipped){
                    std::cout << "Update which saber? 1 or 2\nSelect: ";
                    input = getUserInt();
                    if(input == 1){
                        input = getUserSaberType(true);
                        user_saber_1.updateLightsaberType(input);
                    } else if (input == 2) {
                        input = getUserSaberType(true);
                        user_saber_2.updateLightsaberType(input);
                    } else{
                        std::cout << "Invalid option. Cancelling request\n\n";
                    }
                } else {
                    input = getUserSaberType(false);
                    user_saber_1.updateLightsaberType(input);
                }
                break;
            case(4):
                user_attr.updateAttribute();
                break;
            case(5):
                user_attr.showAttributes();
                break;
            case(6):
                std::cout << "Output: Planet, Location, Container, Num Available\n";
                std::cout << user_saber_1.crystal_1.curString() << ":\n";
                user_saber_1.crystal_1.printLocations(crystal_data);
                std::cout << user_saber_1.crystal_2.curString() << ":\n";
                user_saber_1.crystal_2.printLocations(crystal_data);
                std::cout << "\n";
                break;
            case(7):
                save_cur_build(user_attr, user_saber_1, second_equipped, user_saber_2);
                break;
            case(8):
                load_build(user_attr, user_saber_1, user_saber_2, second_equipped);
                break;
            case(9):
                delete_build();
                break;
            case(10):
                show_saved_builds();
                break;
            case(11):
                if(user_saber_1.getTypeVal() == 1){
                    std::cout << "Cannot intitialize second lightsaber. Currently equipped with a Double-Blade \n\n";
                    break;
                }
                // I believe this is 100% memory leaking and needs to fix later on
                else{
                    if(!second_equipped){
                        user_saber_2 = initializeLightsaber(true);
                        second_equipped = true; // do initialization and stuff prior to this point
                    } else {
                        user_saber_2 = Lightsaber();
                        second_equipped = false;
                    }
                }
            case(12):
                break;
            default:
                std::cout << "user choice unsupported\n\n";
                break;
        }
    }
}