#pragma once
#include "tower.hpp"
#include <string>
class AttackTower : public Tower {
    public:
    AttackTower(std::string name, std::string description, unsigned int strength, unsigned int range, unsigned int cooldown, unsigned int cost, Tower* upgrade) : 
    Tower(name, description, strength, range, cost, upgrade), 
    cooldown_(cooldown), cooldownModifiers_(0), attackCounter_(0), rangeModifiers_(0) {}

    ~AttackTower();

    unsigned int currentCooldown() const;
    
    double cooldownPercentage() const;

    bool canAttack() const;

    void restartCooldown();

    void reload();

    virtual unsigned int getRange() const;

    void addCooldownModifier(int amount);

    void addRangeModifier(int amount);

    void removeModifiers();

    private:
    unsigned int cooldown_;
    unsigned int cooldownModifiers_;
    unsigned int attackCounter_;
    unsigned int rangeModifiers_;

    unsigned int currentRange() const;


};
