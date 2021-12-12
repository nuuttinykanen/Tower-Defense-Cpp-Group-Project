#ifndef MAPSQUARE_CPP
#define MAPSQUARE_CPP
#include "mapsquare.hpp"

    int MapSquare::GetX() const { return x_; }
    int MapSquare::GetY() const { return y_; }

    bool FreeSquare::free() const { return true; }
    std::string FreeSquare::GetType() const { return "free"; }

    bool EnemySquare::free() const { return false; }
    std::string EnemySquare::GetType() const { return "enemy"; }
    std::vector<Enemy*> EnemySquare::GetEnemies() { return enemies_; }
    void EnemySquare::SetNext(EnemySquare* e_square) { next_ = e_square; }
    bool EnemySquare::HasNext() {
        if(this->next_ != nullptr) return true;
        else return false;
    }
    EnemySquare* EnemySquare::GetNext() { return next_; }
    void EnemySquare::SetPrevious(EnemySquare* e_square) { previous_ = e_square; }
    EnemySquare* EnemySquare::GetPrevious() { return previous_; }
    bool EnemySquare::HasPrevious() {
        if(this->previous_ != nullptr) return true;
        else return false;
    }
    void EnemySquare::AddEnemy(Enemy* enemy) {
        enemies_.push_back(enemy);
    }
    bool EnemySquare::RemoveEnemy(Enemy* enemy) {
        for(auto it = enemies_.begin(); it != enemies_.end(); ++it) {
            if(*it == enemy) {
                this->enemies_.erase(it);
                return true;
            }
        }
        return false;
    }
    bool EnemySquare::ContainsEnemies() const {
        if(enemies_.empty()) return false;
        else return true;
    }
    Enemy* EnemySquare::GetEnemy(Enemy* enemy) const {
        for(auto it : enemies_) {
            if(it == enemy) {
                return it;
            }
        }
        return nullptr;
    }

    bool EnemySquare::ContainsEnemy(Enemy* enemy) const {
        if(this->GetEnemy(enemy) != nullptr) return true;
        else return false;
    }
    unsigned int EnemySquare::GetNumber() { return number_; }
    void EnemySquare::SetNumber(unsigned int number) { number_ = number; }

    bool TowerSquare::free() const { return false; }
    std::string TowerSquare::GetType() const { return "tower"; }

    Tower* TowerSquare::GetTower() { return tower_; }
    bool TowerSquare::ContainsTower(Tower* tower) {
        if(tower_ == tower) return true;
        else return false;
    }
    std::vector<EnemySquare*> TowerSquare::EnemySquaresInRange() { return enemySquaresInRange_; }
    void TowerSquare::AddToEnemiesInRange(EnemySquare* es) { enemySquaresInRange_.push_back(es); }

#endif