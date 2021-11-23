#include "projectile.hpp"
#include <cmath>
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
    std::cout << "----------------------" << std::endl;
    std::cout << "BombProjectile attacks square " << enemy->GetX() << " " << enemy->GetY() << "with range " << this->bomb_radius_ << std::endl;

    EnemySquare* prev = enemy->GetPrevious();
    EnemySquare* next = enemy->GetNext();
    for(unsigned int i = 0; i < this->bomb_radius_; i++) {
        if(prev != nullptr) {
            for(auto it : prev->GetEnemies()) {
                std::cout << it->GetName() << " at " << prev->GetX()  << " " << prev->GetY() << " via PREVIOUS" << std::endl;
                it->ChangeHealth(-1);
            }
            prev = prev->GetPrevious();
        }
        if(next != nullptr) {
            for(auto it : next->GetEnemies()) {
                std::cout << it->GetName() << " at " << next->GetX()  << " " << next->GetY() << " via NEXT" << std::endl;
                it->ChangeHealth(-1);
            }
            next = next->GetNext();
        }
    }
    std::cout << "----------------------" << std::endl;
}



