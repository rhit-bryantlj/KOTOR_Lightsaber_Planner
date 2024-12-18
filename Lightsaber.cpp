#include<iostream>
#include<cmath>
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

int Lightsaber::getTypeVal(){
    return saber_type;
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

int Lightsaber::getColorVal(){
    return saber_color_crystal;
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

void Lightsaber::calcStatsWithCrystals(json crystal_data){
    std::vector<std::string> effect_vect_1;
    std::vector<std::string> effect_vect_2;
    std::vector<std::string> extra_effects = {};

    if(crystal_1.getVal() != 0)
        effect_vect_1 = crystal_data[crystal_1.curString()][crystal_1.crystal_stat_choice];
    else{
        effect_vect_1 = {};
    }
    if(crystal_2.getVal() != 0){
        effect_vect_2 = crystal_data[crystal_2.curString()][crystal_2.crystal_stat_choice];
    } else{
        effect_vect_2 = {};
    }
    std::vector<std::string> crystal_vect_arr[2] = {effect_vect_1,effect_vect_2};
    int damage_min_effect = damage_min;
    int damage_max_effect = damage_max;

    int attk_bonus = 0;
    int bb_defl = 0;
    int f_regen = 0;
    int min_crit_add = 0;
    int max_crit_add = 0;
    int keen_crit_update = 0;
    bool keen_added = false;
    bool massive_crit = false;

    for(std::vector<std::string> crystal_vect : crystal_vect_arr){
        for(std::string stat_vect : crystal_vect){
            // getting out damage numbers for regular and ranged
            if(stat_vect.find("Damage: Energy,")!= std::string::npos){
                int pos = stat_vect.find(',') + 1;
                std::string damage_str = stat_vect.substr(pos);
                if(int dash_pos = damage_str.find('-') != std::string::npos){
                    damage_min_effect += stoi(damage_str.substr(0,dash_pos));
                    damage_max_effect = stoi(damage_str.substr(dash_pos+1));
                }else{
                    damage_min_effect += stoi(damage_str);
                    damage_max_effect += stoi(damage_str);
                }
            }

            else if(stat_vect.find("Attack Modifier:") != std::string::npos){
                int plus_pos = stat_vect.find('+') + 1;
                attk_bonus += stoi(stat_vect.substr(plus_pos));
            }

            else if(stat_vect.find("Blaster Bolt") != std::string::npos){
                int plus_pos = stat_vect.find('+') + 1;
                bb_defl += stoi(stat_vect.substr(plus_pos));
            }

            // get out massive criticals, these crystals are all 2-12 so could hardcode,
            // however when I expand to multiple items/kotor 2 they have diff values.
            // Also could hardcode it to be for Opila crystal, but again KOTOR 2
            else if(stat_vect.find("Massive Criticals: +") != std::string::npos){
                int pos2 = stat_vect.find('+') + 1;
                std::string crit_str = stat_vect.substr(pos2);
                int dash_pos = crit_str.find('-');
                min_crit_add = stoi(crit_str.substr(0,dash_pos));
                max_crit_add = stoi(crit_str.substr(dash_pos+1));
                massive_crit = true;
            }

            else if(stat_vect.find("Regeneration Force") != std::string::npos){
                int pos = stat_vect.find(':') + 2;
                f_regen += stoi(stat_vect.substr(pos));
            }

            else if(stat_vect.find("Keen") != std::string::npos){
                if(keen_added == false){
                    keen_added = true;
                    if(crit_min == 20){
                        keen_crit_update = -1;
                    } else if(crit_min == 19){
                        keen_crit_update = -2;
                    }
                }
            }

            // others like Damage Bonus, Ion, Energy vs droid, etc go into list to output directly
            else{
                extra_effects.push_back(stat_vect);
            }
        }
    }
    
    std::cout << "Damage: Energy, " << damage_min_effect << "-" << damage_max_effect << "\n";
    std::cout << "Critical Threat: " << crit_min + keen_crit_update << "-" << crit_max << ", x" << crit_mult;
    
    if(massive_crit){
        std::cout << " Massive Criticals: " << min_crit_add << "-" << max_crit_add << "\n\n";
    }else{
        std::cout << "\n\n";
    }

    if(attk_bonus > 0 )
        std::cout << "Attack Modifier: +" << attk_bonus << "\n";

    if(bb_defl > 0)
        std::cout << "Blaster Bolt Deflection: +" << bb_defl << "\n";
    if(f_regen>0)
        std::cout << "Regeneration Force Points: " << f_regen << "\n";
    for(std::string effect : extra_effects){
        std::cout << effect << "\n";
    }
    std::cout << "\n";
}

void Lightsaber::showCurrentLightsaber(json crystal_data, Attributes user_attr){
    std::cout << "Current Lightsaber Configuration\n";
    std::cout << "---------------------------------\n";
    std::cout << "Lightsaber Type: " << saber_strings[saber_type] << "\n";
    std::cout << "Color Crystal: " << color_strings[saber_color_crystal] << "\n";

    calcStatsWithCrystals(crystal_data);
    if(balanced)
        std::cout << "Balanced: +2/+0 vs. two-weapon penalty if used in the off-hand\n\n";
    std::cout << "Attack bonus from ";
    if(user_attr.getStr() >= user_attr.getDex()){
        std::cout << "Str: " << floor((user_attr.getStr()-10)/2) << "\n\n";
    } else{
        std::cout << "Dex: " << floor((user_attr.getDex()-10)/2)<< "\n\n";
    }
    std::cout << "Crystal 1:\n";
    crystal_1.printStats(crystal_data);
    std::cout << "\nCrystal 2:\n";
    crystal_2.printStats(crystal_data);
    std::cout << "---------------------------------\n\n";
}