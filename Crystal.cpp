#include"Crystal.hpp"
#include<array>

Crystal::Crystal(){
    cur = NO_Crystal;
}

void Crystal::updateCrystal(int select){
    cur = static_cast<UpgradeCrystal>(select);
}

std::string Crystal::curString(){
    return upgrade_strings[cur];
}

void Crystal::setStat(int choice){
    if(choice == 0){
        crystal_stat_choice = "base";
    } else if(choice == 1){
        crystal_stat_choice = "HoG";
    } else{
        crystal_stat_choice = "MoF";
    }
}

int Crystal::getVal(){
    return cur;
}

void Crystal::printLocations(json crystal_data){
    if(cur == NO_Crystal){
        std::cout << "  No Crystal in slot\n";
    }
    else{
        std::cout << crystal_data[upgrade_strings[cur]]["Locations"].dump(1)<< "\n";
    }
}

void Crystal::printStats(json crystal_data){
    std::cout << "Crystal: " << upgrade_strings[cur] << "\n";

    if(cur != NO_Crystal)
        std::cout << crystal_data[upgrade_strings[cur]][crystal_stat_choice].dump() << "\n";
}