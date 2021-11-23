#ifndef SUPPORTTOWER_HPP
#define SUPPORTTOWER_HPP
#include "tower.hpp"
#include "mapsquare.hpp"
#include <string>

class SupportTower : public Tower {
    public:
    SupportTower(std::string name, std::string description, int strength, int range, int cost, Tower* upgrade):
     Tower(name, description, strength, range, cost, upgrade) {}
     ~SupportTower(){}
    
    virtual std::string GetType() const;

};

#endif