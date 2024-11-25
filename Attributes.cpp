#include"Attributes.hpp"
#include<iostream>
#include<map>
#include<string>


Attributes::Attributes(int str, int dex, int con, int intel, int wis, int charisma){
    setAttributes(str, dex, con, intel, wis, charisma);
}

void Attributes::updateStr(int str){
    attributes_["Str"] = str;
}

void Attributes::updateCon(int con){
    attributes_["Con"] = con;
}
void Attributes::updateDex(int dex){
    attributes_["Dex"] = dex;
}

void Attributes::updateInt(int intel){
    attributes_["Int"] = intel;
}

void Attributes::updateWis(int wis){
    attributes_["Wis"] = wis;
}

void Attributes::updateChar(int charisma){
    attributes_["Char"] = charisma;
}

void Attributes::showAttributes(){
    for(auto i : attributes_){
        std::cout << i.first << ": " << i.second << std::endl;
    }
    std::cout << "\n";
}

void Attributes::setAttributes(int str, int dex, int con, int intel, int wis, int charisma){
    attributes_ = {
        {"Str", str},
        {"Dex", dex},
        {"Con", con},
        {"Int", intel},
        {"Wis", wis},
        {"Char", charisma},
    };
}

std::map<std::string,int> Attributes::getAttributes(){
    return attributes_;
}

void Attributes::updateAttribute(){
    int user_in;
    std::cout << "Select Attribute(s) to update:\n(0) Str   (1) Dex   (2) Con\n";
    std::cout << "(3) Int   (4) Wis   (5) Chr (6) All\n";
    std::cin >> user_in;
    std::cout << "\n";

    switch(user_in){
        case 0:
            std::cout << "New Str: ";
            std::cin>> user_in;
            std::cout << "\n";
            updateStr(user_in);
            break;
        case 1:
            std::cout << "New Dex: ";
            std::cin>> user_in;
            std::cout << "\n";
            updateDex(user_in);
            break;
        case 2:
            std::cout << "New Con: ";
            std::cin>> user_in;
            std::cout << "\n";
            updateCon(user_in);
            break;
        case 3:
            std::cout << "New Int: ";
            std::cin>> user_in;
            std::cout << "\n";
            updateInt(user_in);
            break;
        case 4:
            std::cout << "New Wis: ";
            std::cin>> user_in;
            std::cout << "\n";
            updateWis(user_in);
            break;
        case 5:
            std::cout << "New Chr: ";
            std::cin>> user_in;
            std::cout << "\n";
            updateChar(user_in);
            break;
        case 6:
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
            setAttributes(attr[0], attr[1], attr[2], attr[3], attr[4], attr[5]);
            break;
    }

    showAttributes();
}
