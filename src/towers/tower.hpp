#ifndef TOWER_HPP
#define TOWER_HPP
#include <iostream>
#include <utility>
#include <vector>



enum TowerTypes {GunnerType, MultiGunnerType, GunFiendType, BomberType, SuperBomberType, UltraBomberType,
        CursedKidType, MaskedKidType, MaskedGodType, KnifeBotType, KnifeBot2Type, SwordBotType, ClockerType, ClockerBlockerType, SeerType, MotherBrainType,
        StereoType, DJDudeType, Support4
};

class Tower {
    public:
    Tower(std::string name, std::string description, unsigned int strength, unsigned int range, unsigned int price) : name_(std::move(name)), description_(std::move(description)), strength_(strength), range_(range), price_(price) { }

    virtual ~Tower() = default;

    [[nodiscard]] std::string GetName() const;

    [[nodiscard]] std::string GetDescription() const;

    [[nodiscard]] unsigned int GetStrength() const;

    [[nodiscard]] virtual unsigned int GetRange() const;

    [[nodiscard]] unsigned int GetPrice() const;

    virtual bool CanUpgrade() {return true;};

    [[nodiscard]] virtual std::string GetMainType() const = 0;

    [[nodiscard]] virtual TowerTypes getType() const = 0;

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