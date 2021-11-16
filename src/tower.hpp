#pragma once
#include <iostream>
#include <vector>
class Tower {
    public:
    Tower(std::string name, unsigned int strength, unsigned int range, unsigned int price, Tower* upgrade) : name_(name), strength_(strength), range_(range), price_(price), upgrade_(upgrade) { }
    
    ~Tower();

    std::string GetName();

    unsigned int GetStrength();

    unsigned int GetRange();

    unsigned int GetPrice();

    Tower* GetUpgrade();

    bool HasUpgrade();

    private:
    std::string name_;    
    unsigned int strength_;
    unsigned int range_;
    unsigned int price_;
    Tower* upgrade_;
};