#ifndef TOWER_HPP
#define TOWER_HPP
#include <iostream>
#include <vector>
class Tower {
    public:
    Tower(std::string name, std::string description, unsigned int strength, unsigned int range, unsigned int price) : name_(name), strength_(strength), range_(range), price_(price) { }
    
    ~Tower();

    std::string GetName() const;

    std::string GetDescription() const;

    unsigned int GetStrength() const;

    virtual unsigned int GetRange() const;

    unsigned int GetPrice() const;

    virtual std::string GetType() const = 0;

    virtual Tower* Upgrade() = 0;

    private:
    std::string name_;
    std::string description_;    
    unsigned int strength_;
    unsigned int price_;
    protected:
    unsigned int range_;
};
#endif