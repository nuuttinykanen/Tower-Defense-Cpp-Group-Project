#ifndef TOWER_HPP
#define TOWER_HPP
#include <iostream>
#include <vector>
class Tower {
    public:
    Tower(std::string name, std::string description, unsigned int strength, unsigned int range, unsigned int price, std::string upgrade) : name_(name), strength_(strength), range_(range), price_(price), upgrade_(upgrade) { }
    
    ~Tower();

    std::string GetName() const;

    std::string GetDescription() const;

    unsigned int GetStrength() const;

    virtual unsigned int GetRange() const;

    unsigned int GetPrice() const;

    std::string GetUpgrade() const;

    bool HasUpgrade() const;

    virtual std::string GetType() const = 0;

    virtual Tower* Upgrade() = 0;

    private:
    std::string name_;
    std::string description_;    
    unsigned int strength_;
    unsigned int price_;
    std::string upgrade_;
    protected:
    unsigned int range_;
};
#endif