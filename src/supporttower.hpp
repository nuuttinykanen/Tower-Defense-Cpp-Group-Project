#pragma once
#include "tower.hpp"
#include "mapsquare.hpp"
#include <string>

class SuppportTower : public Tower {
    public:
    SupportTower(std::string name, std::string description, int strength, int range, int cost, Tower* upgrade):
     Tower(name, description, strength, range, cost, upgrade) {}
     ~SupportTower(){}
    
    virtual void supportEffect(square: MapSquare) = 0 {}

};