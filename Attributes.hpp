#include<map>
#include<string>

class Attributes{
public:
    Attributes(int str, int dex, int con, int intel, int wis, int charisma);
    void updateStr(int str);
    void updateCon(int con);
    void updateDex(int dex);
    void updateInt(int intel);
    void updateWis(int wis);
    void updateChar(int charisma);
    void setAttributes(int str, int dex, int con, int intel, int wis, int charisma);
    void showAttributes();

    std::map<std::string,int> getAttributes();
    int getStr();
    int getDex();
    void updateAttribute();
    
private:
    std::map<std::string,int> attributes_;
};
