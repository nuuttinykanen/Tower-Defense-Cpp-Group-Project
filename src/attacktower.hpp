#pragma once
#include "tower.hpp"
#include <string>
#include "enemy.hpp"
class AttackTower : public Tower {
    public:
    AttackTower(std::string name, std::string description, unsigned int strength, unsigned int range, unsigned int cooldown, unsigned int cost, Tower* upgrade) : 
    Tower(name, description, strength, range, cost, upgrade), 
    cooldown_(cooldown), cooldownModifiers_(0), attackCounter_(0), rangeModifiers_(0) {}

    ~AttackTower(){};

    unsigned int CurrentCooldown() const;
    
    double CooldownPercentage() const;

    bool CanAttack() const;

    void RestartCooldown();

    void Reload();

    void AddCooldownModifier(int amount);

    void AddRangeModifier(int amount);

    void RemoveModifiers();

    unsigned int GetCurrentRange() const;

    virtual Projectile* GetProjectile() = 0; 

    private:
    unsigned int cooldown_;
    unsigned int cooldownModifiers_;
    unsigned int attackCounter_;
    unsigned int rangeModifiers_;

    unsigned int CurrentRange() const;

    virtual std::string GetType() const;
};

class Bomber : public AttackTower {
    public:
    Bomber() : AttackTower("Bomber", "Bombs enemies.", 1, 3, 10, 500, nullptr) { }
    ~Bomber(){}
    virtual Projectile* GetProjectile(); 
};

class Gunner : public AttackTower {
    public:
    Gunner() : AttackTower("Gunner", "Guns enemies.", 1, 3, 10, 500, nullptr) { }
    ~Gunner(){}
    virtual Projectile* GetProjectile(); 
};