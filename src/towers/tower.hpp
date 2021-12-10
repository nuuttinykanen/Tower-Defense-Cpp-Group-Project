#ifndef TOWER_HPP
#define TOWER_HPP
#include <iostream>
#include <vector>



enum TowerTypes {GunnerType, MultiGunnerType, GunFiendType, BomberType, SuperBomberType, UltraBomberType,
        Attack3, Attack4, ClockerType, ClockerBlockerType, SeerType, MotherBrainType,
        StereoType, DJDudeType, Support4
};

class Tower {
    public:
    Tower(std::string name, std::string description, unsigned int strength, unsigned int range, unsigned int price) : name_(name), description_(description), strength_(strength), range_(range), price_(price) { }

    virtual ~Tower() = default;

    std::string GetName() const;

    std::string GetDescription() const;

    unsigned int GetStrength() const;

    virtual unsigned int GetRange() const;

    unsigned int GetPrice() const;

    virtual bool CanUpgrade() {return true;};

    virtual std::string GetMainType() const = 0;

    virtual TowerTypes getType() const = 0;

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