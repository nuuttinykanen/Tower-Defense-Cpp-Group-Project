#include "tower.hpp"

    Tower::~Tower() {
        delete upgrade_;
    }

    std::string Tower::GetName() { return name_; }

    unsigned int Tower::GetStrength() { return strength_; }

    unsigned int Tower::GetRange() { return range_; }

    unsigned int Tower::GetPrice() { return price_; }

    Tower* Tower::GetUpgrade() { return upgrade_; }
    
    bool Tower::HasUpgrade() { 
        if(upgrade_ == nullptr) return false;
        else return true;
    }