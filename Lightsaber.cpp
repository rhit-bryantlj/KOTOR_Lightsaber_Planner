#include<iostream>
#include "Lightsaber.hpp"

using json = nlohmann::json;

Lightsaber::Lightsaber(int saber_sel, int color_sel, int crystal1, int crystal2){
    updateLightsaberType(saber_sel);
    updateColorCrystal(color_sel);
    
    crystal_1.updateCrystal(crystal1);
    crystal_2.updateCrystal(crystal2);

    damage_min = 2;
}

void Lightsaber::updateLightsaberType(int saber_sel){
    saber_type = static_cast<LightsaberType>(saber_sel);
    switch(saber_type){
        case Single:
            damage_max = 16;
            crit_min = 19;
            balanced = false;
            break;
        case Double:
            damage_max = 20;
            crit_min = 20;
            balanced = true;
            break;
        case Short:
            damage_max = 12;
            crit_min = 19;
            balanced = true;
            break;
        default:
            damage_max = 16;
            crit_min = 19;
            balanced = false;
            break;
    };
}

void Lightsaber::updateColorCrystal(int color_sel){
    saber_color_crystal = static_cast<ColorCrystal>(color_sel);

    if(saber_color_crystal == Heart_of_Guardian){
        crystal_1.setStat(1);
        crystal_2.setStat(1);
    } else if(saber_color_crystal == Mantle_of_Force){
        // update crystals to MoF stats
        crystal_1.setStat(2);
        crystal_2.setStat(2);
    } else{
        //update to basic stats on crystals
        crystal_1.setStat(0);
        crystal_2.setStat(0);
    }
}

void Lightsaber::updateCrystal1(int selected){
    if(selected == crystal_1.getVal()){
        return;
    }

    crystal_1.updateCrystal(selected);
}

void Lightsaber::updateCrystal2(int selected){
    if(selected == crystal_2.getVal()){
        return;
    }
    crystal_2.updateCrystal(selected);
}

void Lightsaber::showCurrentLightsaber(json crystal_data){
    std::cout << "Current Lightsaber Configuration\n";
    std::cout << "---------------------------------\n";
    std::cout << "Lightsaber Type: " << saber_strings[saber_type] << "\n";
    std::cout << "Color Crystal: " << color_strings[saber_color_crystal] << "\n";

    std::cout << "Damage: Energy, " << damage_min << "-" << damage_max << "\n";
    std::cout << "Critical Threat: " << crit_min << "-" << crit_max << ", x" << crit_mult << "\n\n";
    if(balanced)
        std::cout << "Balanced: +2/+0 vs. two-weapon penalty if used in the off-hand\n\n";
    std::cout << "Crystal 1 Stats:\n";
    crystal_1.printStats(crystal_data);
    std::cout << "\nCrystal 2 Stats:\n";
    crystal_2.printStats(crystal_data);
    std::cout << "---------------------------------\n\n";
}