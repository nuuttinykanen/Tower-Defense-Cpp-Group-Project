#ifndef PROJECTILE_HPP
#define PROJECTILE_HPP

#include "enemy.hpp"
#include "mapsquare.hpp"
#include "tower.hpp"
class Projectile {
    public:
    Projectile(Tower* sender) : sender_(sender) {
        location_ = nullptr;
        target_ = nullptr;
        strength_ = sender->GetStrength();
        to_be_removed_ = false;
    }
    ~Projectile(){}
    void Initialize(MapSquare* start_loc, Enemy* target);
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
    protected:
    bool to_be_removed_;
};

class BombProjectile : public Projectile {
    public:
    BombProjectile(Tower* sender) : Projectile(sender) {
        bomb_radius_ = 2;
    }
    void Effect(EnemySquare* enemy);
    private: 
    unsigned int bomb_radius_;
};

class BulletProjectile : public Projectile {
    public:
    BulletProjectile(Tower* sender) : Projectile(sender) { }
    void Effect(EnemySquare* enemy);
};

#endif