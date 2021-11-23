#ifndef PROJECTILE_HPP
#define PROJECTILE_HPP

#include "enemy.hpp"
#include "mapsquare.hpp"
#include "tower.hpp"
class Projectile {
    public:
    Projectile(Tower* sender, MapSquare* start_loc, Enemy* target) : sender_(sender), location_(start_loc), target_(target) {
        strength_ = sender->GetStrength();
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
    BombProjectile(Tower* sender, MapSquare* start_loc, Enemy* target) : Projectile(sender, start_loc, target) {
        bomb_radius_ = 2;
    }
    void Effect(EnemySquare* enemy);
    private: 
    unsigned int strength_;
    unsigned int bomb_radius_;
};

#endif