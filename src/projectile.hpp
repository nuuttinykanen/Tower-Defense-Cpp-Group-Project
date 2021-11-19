#ifndef PROJECTILE_HPP
#define PROJECTILE_HPP

#include "enemy.hpp"
#include "tower.hpp"

class Projectile {
    public:
    Projectile(Tower* sender, unsigned int strength) : sender_(sender), strength_(strength)  {
        location_ = nullptr;
        target_ = nullptr;
        to_be_removed_ = false;
    }
    ~Projectile(){}
    Tower* GetSender();
    MapSquare* GetLocation();
    Enemy* GetTarget();
    void SetTarget(Enemy* target);
    unsigned int GetStrength();
    void ChangeLocation(MapSquare* square);
    void SetRemovalTrue();
    bool ToBeRemoved();
    virtual void Effect(EnemySquare* enemy) = 0;

    private:
    Tower* sender_;
    MapSquare* location_;
    Enemy* target_;
    unsigned int strength_;
    bool to_be_removed_;
};

class BombProjectile : public Projectile {
    public:
    BombProjectile(Tower* sender) : Projectile(sender, sender->GetStrength()) { }
    void Effect(EnemySquare* enemy);
};

#endif