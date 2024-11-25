#include"Crystal.hpp"

enum LightsaberType{
    Single,
    Double,
    Short
};

enum ColorCrystal{
    Blue,
    Green,
    Red,
    Yellow,
    Purple,
    Heart_of_Guardian,
    Mantle_of_Force
};

class Lightsaber{
    LightsaberType saber_type;
    Crystal crystal_1, crystal_2;
    ColorCrystal saber_color_crystal;
    int damage_min, damage_max, crit_min;
    bool balanced;
    int crit_max = 20;
    int crit_mult = 2;

    public:
        Lightsaber(int saber_sel, int color_sel, int crystal1, int crystal2);
        void updateLightsaberType(int saber_sel);
        void updateColorCrystal(int color_sel);
        void updateCrystal1(int selected);
        void updateCrystal2(int selected);
        void showCurrentLightsaber(json crystal_data);
    
    private:
        std::map<int, std::string> saber_strings = {
            {0, "Single Blade"},
            {1, "Double Blade"},
            {2, "Short Lighsaber"}
        };

        std::map<int, std::string> color_strings = {
            {0, "Blue"},
            {1, "Green"},
            {2, "Red"},
            {3, "Yellow"},
            {4, "Purple"},
            {5, "Heart of Guardian (Orange)"},
            {6, "Mantle of the Force (Cyan)"}
        };
};