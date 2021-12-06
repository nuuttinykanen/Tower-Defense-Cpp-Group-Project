#include "tower.hpp"

    Tower::~Tower() { }

    std::string Tower::GetName() const { return name_; }

    std::string Tower::GetDescription() const { return description_; } 

    unsigned int Tower::GetStrength() const { return strength_; }

    unsigned int Tower::GetRange() const { return range_; }

    unsigned int Tower::GetPrice() const { return price_; }

    std::string Tower::GetUpgrade() const { return upgrade_; }
    
    bool Tower::HasUpgrade() const { 
        if(this->GetUpgrade() != "") return true;
        else return false;
    }