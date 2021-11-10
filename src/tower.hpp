#pragma once
#include <iostream>
#include <vector>
class Tower {
    public:
    Tower(std::string name, unsigned int strength, unsigned int range, unsigned int price, Tower* upgrade) : name_(name), strength_(strength), range_(range), price_(price), upgrade_(upgrade) { }
    ~Tower() { }
    std::string GetName() { return name_; }
    unsigned int GetStrength() { return strength_; }
    unsigned int GetRange() { return range_; }
    unsigned int GetPrice() { return price_; }
    Tower* GetUpgrade() { return upgrade_; }
    bool HasUpgrade() { 
        if(upgrade_ == nullptr) return false;
        else return true;
    }

    private:
    std::string name_;    
    unsigned int strength_;
    unsigned int range_;
    unsigned int price_;
    Tower* upgrade_;
};