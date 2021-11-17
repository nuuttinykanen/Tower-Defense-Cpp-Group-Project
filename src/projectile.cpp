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
    std::cout << "BOOM!" << std::endl;
}

