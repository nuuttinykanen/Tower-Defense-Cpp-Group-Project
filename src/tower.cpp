#include "tower.hpp"
#include "supporttower.hpp"

#include "attacktower.hpp"

    std::string Tower::GetName() const { return name_; }

    std::string Tower::GetDescription() const { return description_; }

    unsigned int Tower::GetStrength() const { return strength_; }

    unsigned int Tower::GetRange() const { return range_; }

    unsigned int Tower::GetPrice() const { return price_; }

