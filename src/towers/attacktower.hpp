#pragma once
#include "tower.hpp"
#include <string>
#include <utility>
#include "../enemy.hpp"
#include "../projectile.hpp"
class AttackTower : public Tower {
    public:
    AttackTower(std::string name, std::string description, unsigned int strength, unsigned int range, int cooldown, unsigned int cost) :
    Tower(std::move(name), std::move(description), strength, range, cost),
    cooldownLimit_(cooldown), cooldown_(0), cooldownModifiers_(0), attackCounter_(0), rangeModifiers_(0) {}

    ~AttackTower() override = default;;

    [[nodiscard]] int CurrentCooldown() const;

    [[nodiscard]] int GetCooldownLimit() const;

    [[nodiscard]] bool CanAttack() const;

    void RestartCooldown();

    void Reload();

    void AddCooldownModifier(int amount);

    void AddRangeModifier(int amount);

    void ResetModifiers();

    virtual Projectile* GetProjectile() = 0;

    [[nodiscard]] unsigned int GetRange() const override;

    private:
    int cooldownLimit_;
    int cooldown_;
    int cooldownModifiers_;
    unsigned int attackCounter_;
    unsigned int rangeModifiers_;



    [[nodiscard]] std::string GetMainType() const override;
};

class Bomber : public AttackTower {
    public:
    Bomber() : AttackTower("Bomber", "Launches bombs that also deal\ndamage to enemies next to a target", 6, 2, 60, 200) { }
    ~Bomber() override= default;
    Projectile* GetProjectile() override;

    [[nodiscard]] TowerTypes getType() const override {return TowerTypes::BomberType;}

    Tower* Upgrade() override;
};

class SuperBomber : public AttackTower {
    public:
    SuperBomber() : AttackTower("Super Bomber", "Launches bombs that also deal\ndamage to enemies next to a target", 7, 3, 90, 510) { }
    Projectile* GetProjectile() override;

    [[nodiscard]] TowerTypes getType() const override {return TowerTypes::SuperBomberType;}

    Tower* Upgrade() override;
};

class UltraBomber : public AttackTower {
    public:
    UltraBomber() : AttackTower("Ultra Bomber", "Launches bombs that also deal\ndamage to enemies next to a target", 10, 4, 120, 700) { }
    Projectile* GetProjectile() override;

    bool CanUpgrade() override {return false;}

    [[nodiscard]] TowerTypes getType() const override {return TowerTypes::UltraBomberType;}

    Tower* Upgrade() override;
};

class Gunner : public AttackTower {
    public:
    Gunner() : AttackTower("Gunner", "Guns enemies.", 2, 5, 30, 50) { }
    ~Gunner() override= default;
    Projectile* GetProjectile() override;

    [[nodiscard]] TowerTypes getType() const override {return TowerTypes::GunnerType;}

    Tower* Upgrade() override;
};

class Multigunner : public AttackTower {
    public:
    Multigunner() : AttackTower("Multigunner", "Same gunner. More guns.", 4, 5, 20, 75) { }
    ~Multigunner()  override = default;
    Projectile* GetProjectile() override;

    [[nodiscard]] TowerTypes getType() const override {return TowerTypes::MultiGunnerType;}

    Tower* Upgrade() override;
};

class GunFiend : public AttackTower {
    public:
    GunFiend() : AttackTower("Gun Fiend", "The gunner became a gun themselves.", 6, 6, 18, 100) { }
    ~GunFiend() override= default;
    Projectile* GetProjectile() override;

    bool CanUpgrade() override {return false;}

    [[nodiscard]] TowerTypes getType() const override {return TowerTypes::GunFiendType;}

    Tower* Upgrade() override;
};

class CursedKid : public AttackTower {
public:
    CursedKid() : AttackTower("Cursed Kid", "Damages and sends enemies back by \ntwo squares.", 2, 1, 100, 400) { }
    ~CursedKid() override = default;
    Projectile* GetProjectile() override;

    [[nodiscard]] TowerTypes getType() const override {return TowerTypes::CursedKidType;}

    Tower* Upgrade() override;
};

class MaskedKid : public AttackTower {
public:
    MaskedKid() : AttackTower("Masked Kid", "Damages and sends enemies back\nby three squares.", 2, 1, 120, 420) { }
    ~MaskedKid() override= default;
    Projectile* GetProjectile() override;

    [[nodiscard]] TowerTypes getType() const override {return TowerTypes::MaskedKidType;}

    Tower* Upgrade() override;
};

class MaskedGod : public AttackTower {
public:
    MaskedGod() : AttackTower("Masked God", "Damages and sends enemies back\nby five squares.", 2, 1, 160, 450) { }
    ~MaskedGod() override= default;
    Projectile* GetProjectile() override;

    [[nodiscard]] TowerTypes getType() const override {return TowerTypes::MaskedGodType;}

    Tower* Upgrade() override;
};

class KnifeBot : public AttackTower {
public:
    KnifeBot() : AttackTower("Knife Bot", "Attacks close and hard.", 8, 1, 100, 100) { }
    ~KnifeBot() override= default;
    Projectile* GetProjectile() override;

    [[nodiscard]] TowerTypes getType() const override {return TowerTypes::KnifeBotType;}

    Tower* Upgrade() override;
};

class KnifeBot2 : public AttackTower {
public:
    KnifeBot2() : AttackTower("Knife Bot 2.0", "Attacks close and hard.", 16, 1, 100, 110) { }
    ~KnifeBot2(){}
    Projectile* GetProjectile() override;

    [[nodiscard]] TowerTypes getType() const override {return TowerTypes::KnifeBot2Type;}

    Tower* Upgrade() override;
};

class SwordBot : public AttackTower {
public:
    SwordBot() : AttackTower("Sword Bot", "Attacks close and hard.", 20, 2, 100, 130) { }
    ~SwordBot() override= default;
    Projectile* GetProjectile() override;

    [[nodiscard]] TowerTypes getType() const override {return TowerTypes::SwordBotType;}

    Tower* Upgrade() override;
};