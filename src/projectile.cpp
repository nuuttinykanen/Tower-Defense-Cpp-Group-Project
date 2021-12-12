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

std::vector<std::pair<int, int>> BombProjectile::Effect(EnemySquare* enemy) {
    std::vector<std::pair<int, int>> list = std::vector<std::pair<int, int>>();
    if(enemy == nullptr) return list;
    for(auto en : enemy->GetEnemies()) {
        en->ChangeHealth(-1 * this->GetStrength());
        list.emplace_back(std::make_pair(enemy->GetX(), enemy->GetY()));
    }
    EnemySquare* prev = enemy->GetPrevious();
    EnemySquare* next = enemy->GetNext();
    for(unsigned int i = 0; i < this->bomb_radius_; i++) {
        if(prev != nullptr) {
            for(auto it : prev->GetEnemies()) {
                it->ChangeHealth(-1 * this->GetStrength());
                list.emplace_back(std::make_pair(prev->GetX(), prev->GetY()));
            }
            prev = prev->GetPrevious();
        }
        if(next != nullptr) {
            for(auto it : next->GetEnemies()) {
                it->ChangeHealth(-1 * this->GetStrength());
                list.emplace_back(std::make_pair(next->GetX(), next->GetY()));
            }
            next = next->GetNext();
        }
    }
    this->to_be_removed_ = true;
    return list;
}

std::string BombProjectile::GetType() {
    return "bomb";
}

std::vector<std::pair<int, int>> BulletProjectile::Effect(EnemySquare* enemy) {
    std::vector<std::pair<int, int>> list = std::vector<std::pair<int, int>>();
    this->to_be_removed_ = true;
    if(enemy == nullptr) return list;
    if(this->GetTarget() != nullptr) {
        Enemy* target = enemy->GetEnemy(this->GetTarget());
        if(target != nullptr) {
            target->ChangeHealth(-1 * this->GetStrength());
            list.emplace_back(std::make_pair(enemy->GetX(), enemy->GetY()));
        }
    }
    return list;
}

std::string BulletProjectile::GetType() {
    return "bullet";
}


std::string CursedProjectile::GetType() {
    return "cursed";
}

std::vector<std::pair<int, int>> CursedProjectile::Effect(EnemySquare *enemy) {
    this->to_be_removed_ = true;
    std::vector<std::pair<int, int>> list = std::vector<std::pair<int, int>>();
    if(enemy == nullptr || enemy->GetEnemies().empty() || !this->GetTarget() || !enemy->ContainsEnemy(this->GetTarget())) return list;
    this->GetTarget()->ChangeHealth(-1 * this->GetStrength());
    list.emplace_back(std::make_pair(enemy->GetX(), enemy->GetY()));
    EnemySquare* prev = enemy->GetPrevious();
    if(!prev) return list;
    for(int i = 1; i < squares_back_; i++) {
        if(!prev->GetPrevious()) break;
        prev = prev->GetPrevious();
    }
    prev->AddEnemy(this->GetTarget());
    enemy->RemoveEnemy(this->GetTarget());
    list.emplace_back(std::make_pair(prev->GetX(), prev->GetY()));
    return list;
}
