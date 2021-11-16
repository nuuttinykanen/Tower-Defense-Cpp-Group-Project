#pragma once
#include <iostream>
#include <vector>
class Tower {
    public:
    Tower(std::string name, unsigned int strength, unsigned int range, unsigned int price, Tower* upgrade) : name_(name), strength_(strength), range_(range), price_(price), upgrade_(upgrade) { }
    
    ~Tower();

    std::string GetName() const;

    unsigned int GetStrength() const;

    virtual unsigned int GetRange() const;

    unsigned int GetPrice() const;

    Tower* GetUpgrade() const;

    bool HasUpgrade() const;

    private:
    std::string name_;    
    unsigned int strength_;
    unsigned int range_;
    unsigned int price_;
    Tower* upgrade_;
};