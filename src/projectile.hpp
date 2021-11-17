#ifndef PROJECTILE_HPP
#define PROJECTILE_HPP

#include "enemy.hpp"
#include "tower.hpp"

class Projectile {
    public:
    Projectile(Tower* sender,  MapSquare* location, Enemy* target, unsigned int strength) : sender_(sender), target_(target), strength_(strength), location_(location) {
        to_be_removed_ = false;
    }
    ~Projectile(){}
    MapSquare* GetLocation();
    Enemy* GetTarget();
    unsigned int GetStrength();
    void ChangeLocation(MapSquare* square);
    void SetRemovalTrue();
    bool ToBeRemoved();

    private:
    Tower* sender_;
    MapSquare* location_;
    Enemy* target_;
    unsigned int strength_;
    bool to_be_removed_;
};

#endif