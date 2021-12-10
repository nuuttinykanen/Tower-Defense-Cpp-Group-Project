#ifndef PROJECTILE_HPP
#define PROJECTILE_HPP

#include "enemy.hpp"
#include "mapsquare.hpp"
#include "towers/tower.hpp"
class Projectile {
    public:
    Projectile(Tower* sender) : sender_(sender) {
        location_ = nullptr;
        target_ = nullptr;
        strength_ = sender->GetStrength();
        to_be_removed_ = false;
    }
    virtual ~Projectile() = default;
    void Initialize(MapSquare* start_loc, Enemy* target);
    Tower* GetSender();
    MapSquare* GetLocation();
    Enemy* GetTarget();
    void SetTarget(Enemy* target);
    unsigned int GetStrength();
    void ChangeLocation(MapSquare* square);
    void SetRemovalTrue();
    bool ToBeRemoved();
    virtual std::vector<std::pair<int, int>> Effect(EnemySquare* enemy) = 0;
    virtual std::string GetType() = 0;

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
    ~BombProjectile() override { }
    std::vector<std::pair<int, int>> Effect(EnemySquare* enemy);
    virtual std::string GetType();
    private: 
    unsigned int bomb_radius_;
};

class BulletProjectile : public Projectile {
    public:
    BulletProjectile(Tower* sender) : Projectile(sender) { }
    ~BulletProjectile() override { }
    virtual std::string GetType();
    std::vector<std::pair<int, int>> Effect(EnemySquare* enemy);
};

#endif