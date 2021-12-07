#pragma once
#include "tower.hpp"
#include <string>
#include "enemy.hpp"
#include "projectile.hpp"
class AttackTower : public Tower {
    public:
    AttackTower(std::string name, std::string description, unsigned int strength, unsigned int range, unsigned int cooldown, unsigned int cost) :
    Tower(name, description, strength, range, cost),
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
    Bomber() : AttackTower("Bomber", "Bombs enemies.", 1, 4, 20, 500) { }
    ~Bomber(){}
    virtual Projectile* GetProjectile();
    virtual Tower* Upgrade();
};

class SuperBomber : public AttackTower {
    public:
    SuperBomber() : AttackTower("Super Bomber", "Super bombs enemies", 2, 10, 15, 510) { }
    virtual Projectile* GetProjectile();
    virtual Tower* Upgrade();
};

class UltraBomber : public AttackTower {
    public:
    UltraBomber() : AttackTower("Ultra Bomber", "Ultra bombs enemies", 2, 10, 15, 510) { }
    virtual Projectile* GetProjectile();
    virtual Tower* Upgrade();
};

class Gunner : public AttackTower {
    public:
    Gunner() : AttackTower("Gunner", "Guns enemies.", 1, 5, 20, 500) { }
    ~Gunner(){}
    virtual Projectile* GetProjectile();
    virtual Tower* Upgrade();
};

class Multigunner : public AttackTower {
    public:
    Multigunner() : AttackTower("Multigunner", "Same gunner. More guns.", 1, 5, 20, 500) { }
    ~Multigunner(){}
    virtual Projectile* GetProjectile();
    virtual Tower* Upgrade();
};

class GunFiend : public AttackTower {
    public:
    GunFiend() : AttackTower("Gun Fiend", "The gunner became a gun themselves.", 1, 5, 20, 500) { }
    ~GunFiend(){}
    virtual Projectile* GetProjectile();
    virtual Tower* Upgrade();
};