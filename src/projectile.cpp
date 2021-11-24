#include "projectile.hpp"
#include <cmath>

void Projectile::Initialize(MapSquare* start_loc, Enemy* target) {
    location_ = start_loc;
    target_ = target;
}

MapSquare* Projectile::GetLocation() { return location_; }

void Projectile::ChangeLocation(MapSquare* square) {
    location_ = square;
}

void Projectile::SetRemovalTrue() { to_be_removed_ = true; }

Tower* Projectile::GetSender() { return sender_; }

Enemy* Projectile::GetTarget() { return target_; }

void Projectile::SetTarget(Enemy* target) { target_ = target; }

unsigned int Projectile::GetStrength() { return strength_; }

bool Projectile::ToBeRemoved() { return to_be_removed_; }

void BombProjectile::Effect(EnemySquare* enemy) {
    if(enemy == nullptr) return;
    for(auto en : enemy->GetEnemies()) {
        en->ChangeHealth(-1 * this->GetStrength());
    }
    EnemySquare* prev = enemy->GetPrevious();
    EnemySquare* next = enemy->GetNext();
    for(unsigned int i = 0; i < this->bomb_radius_; i++) {
        if(prev != nullptr) {
            for(auto it : prev->GetEnemies()) {
                std::cout << "hit" << std::endl;
                it->ChangeHealth(-1 * this->GetStrength());
            }
            prev = prev->GetPrevious();
        }
        if(next != nullptr) {
            for(auto it : next->GetEnemies()) {
                std::cout << "hit" << std::endl;
                it->ChangeHealth(-1 * this->GetStrength());
            }
            next = next->GetNext();
        }
    }
    this->to_be_removed_ = true;
}

void BulletProjectile::Effect(EnemySquare* enemy) {
    if(enemy == nullptr) return;
    if(this->GetTarget() != nullptr) {
        Enemy* target = enemy->GetEnemy(this->GetTarget());
        if(target != nullptr) {
            target->ChangeHealth(-1 * this->GetStrength());
        }
    }
}



