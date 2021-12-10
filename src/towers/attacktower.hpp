#pragma once
#include "tower.hpp"
#include <string>
#include "../enemy.hpp"
#include "../projectile.hpp"
class AttackTower : public Tower {
    public:
    AttackTower(std::string name, std::string description, unsigned int strength, unsigned int range, unsigned int cooldown, unsigned int cost) :
    Tower(name, description, strength, range, cost),
    cooldown_(cooldown), cooldownModifiers_(0), attackCounter_(0), rangeModifiers_(0) {}

    ~AttackTower() override = default;;

    unsigned int CurrentCooldown() const;
    
    double CooldownPercentage() const;

    bool CanAttack() const;

    void RestartCooldown();

    void Reload();

    void AddCooldownModifier(int amount);

    void AddRangeModifier(int amount);

    void ResetModifiers();

    unsigned int GetCurrentRange() const;

    virtual Projectile* GetProjectile() = 0;

    virtual unsigned int GetRange() const;

    private:
    unsigned int cooldown_;
    unsigned int cooldownModifiers_;
    unsigned int attackCounter_;
    unsigned int rangeModifiers_;



    virtual std::string GetMainType() const;
};

class Bomber : public AttackTower {
    public:
    Bomber() : AttackTower("Bomber", "Bombs enemies.", 1, 2, 20, 500) { }
    ~Bomber(){}
    virtual Projectile* GetProjectile();

    virtual TowerTypes getType() const {return TowerTypes::BomberType;}

    virtual Tower* Upgrade();
};

class SuperBomber : public AttackTower {
    public:
    SuperBomber() : AttackTower("Super Bomber", "Super bombs enemies", 2, 3, 15, 510) { }
    virtual Projectile* GetProjectile();

    virtual TowerTypes getType() const {return TowerTypes::SuperBomberType;}

    virtual Tower* Upgrade();
};

class UltraBomber : public AttackTower {
    public:
    UltraBomber() : AttackTower("Ultra Bomber", "Ultra bombs enemies", 2, 4, 100, 510) { }
    virtual Projectile* GetProjectile();

    bool CanUpgrade() override {return false;}

    virtual TowerTypes getType() const {return TowerTypes::UltraBomberType;}

    virtual Tower* Upgrade();
};

class Gunner : public AttackTower {
    public:
    Gunner() : AttackTower("Gunner", "Guns enemies.", 1, 5, 20, 500) { }
    ~Gunner(){}
    virtual Projectile* GetProjectile();

    virtual TowerTypes getType() const {return TowerTypes::GunnerType;}

    virtual Tower* Upgrade();
};

class Multigunner : public AttackTower {
    public:
    Multigunner() : AttackTower("Multigunner", "Same gunner. More guns.", 1, 5, 20, 500) { }
    ~Multigunner(){}
    virtual Projectile* GetProjectile();

    virtual TowerTypes getType() const {return TowerTypes::MultiGunnerType;}

    virtual Tower* Upgrade();
};

class GunFiend : public AttackTower {
    public:
    GunFiend() : AttackTower("Gun Fiend", "The gunner became a gun themselves.", 1, 2, 20, 500) { }
    ~GunFiend(){}
    virtual Projectile* GetProjectile();

    bool CanUpgrade() override {return false;}

    virtual TowerTypes getType() const {return TowerTypes::GunFiendType;}

    virtual Tower* Upgrade();
};