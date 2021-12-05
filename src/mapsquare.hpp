#ifndef MAPSQUARE_HPP
#define MAPSQUARE_HPP
#include <string>
#include <vector>
#include "enemy.hpp"
#include "tower.hpp"
class MapSquare {
    public:
    MapSquare(int x, int y) : x_(x), y_(y) { }
    ~MapSquare(){} 
    virtual bool free() const = 0;
    virtual std::string GetType() const = 0;
    int GetX() const { return x_; }
    int GetY() const { return y_; }
    void PrintLocation() { std::cout << "(" << this->GetX() << ", " << this->GetY() << ")" << std::endl; }
    private: 
    int const x_;
    int const y_;
};

class FreeSquare : public MapSquare { 

    public: 
    FreeSquare(int x, int y) : MapSquare(x, y){} 
    ~FreeSquare(){} 
    virtual bool free() const { return true; }
    virtual std::string GetType() const { return "free"; } 
};

class EnemySquare : public MapSquare { 
    public: 
    EnemySquare(int x, int y) : MapSquare(x, y) {
        enemies_ = std::vector<Enemy*>();
        next_ = nullptr;
        previous_ = nullptr;
        number_ = -1;
    } 
    ~EnemySquare(){} 
    virtual bool free() const { return false; }
    virtual std::string GetType() const { return "enemy"; }
    std::vector<Enemy*> GetEnemies() { return enemies_; }
    void SetNext(EnemySquare* e_square) { next_ = e_square; }
    bool HasNext() { 
        if(this->next_ != nullptr) return true;
        else return false;
    }
    EnemySquare* GetNext() { return next_; }
    void SetPrevious(EnemySquare* e_square) { previous_ = e_square; }
    EnemySquare* GetPrevious() { return previous_; }
    bool HasPrevious() { 
        if(this->previous_ != nullptr) return true;
        else return false;
    }
    void AddEnemy(Enemy* enemy) {
        enemies_.push_back(enemy);
    }
    bool RemoveEnemy(Enemy* enemy) {
        for(auto it = enemies_.begin(); it != enemies_.end(); it++) {
            if(*it == enemy) {
                this->enemies_.erase(it);
                return true;
            }
        }
        return false;
    }
    bool ContainsEnemies() const {
        if(enemies_.empty()) return false;
        else return true;
    }
    Enemy* GetEnemy(Enemy* enemy) const {
        for(auto it : enemies_) {
            if(it == enemy) {
                return it;
            }
        }
        return nullptr;
    }

    bool ContainsEnemy(Enemy* enemy) const {
        if(this->GetEnemy(enemy) != nullptr) return true;
        else return false;
    }
    unsigned int GetNumber() { return number_; }
    void SetNumber(unsigned int number) { number_ = number; }

    private:
    std::vector<Enemy*> enemies_;
    EnemySquare* next_; 
    EnemySquare* previous_;
    unsigned int number_;
};

class TowerSquare : public MapSquare {
public:
    TowerSquare(int x, int y, Tower* tower) : MapSquare(x, y), tower_(tower) {
        enemySquaresInRange_ = std::vector<EnemySquare*>();
    }
    ~TowerSquare(){}
    virtual bool free() const { return false; }
    virtual std::string GetType() const { return "tower"; }

    Tower* GetTower() { return tower_; }
    bool ContainsTower(Tower* tower) {
        if(tower_ == tower) return true;
        else return false;
    }
    std::vector<EnemySquare*> EnemySquaresInRange() { return enemySquaresInRange_; }
    void AddToEnemiesInRange(EnemySquare* es) { enemySquaresInRange_.push_back(es); }

private:
    Tower* tower_;
    std::vector<EnemySquare*> enemySquaresInRange_;
};
#endif