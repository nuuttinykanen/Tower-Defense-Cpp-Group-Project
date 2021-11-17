#include "tower.hpp"
#include <string>
#include <vector>
#include "enemy.hpp"
class MapSquare {
    public:
    MapSquare(int x, int y) : x_(x), y_(y) { }
    ~MapSquare(){} 
    virtual bool free() const = 0;
    virtual bool occupied() const = 0;
    virtual std::string type() const = 0;
    int GetX() { return x_; }
    int GetY() { return y_; }
    private: 
    int x_;
    int y_;
};

class FreeSquare : public MapSquare { 

    public: 
    FreeSquare(int x, int y) : MapSquare(x, y){} 
    ~FreeSquare(){} 
    virtual bool free() const { return true; } 
    virtual bool occupied() const { return false; }
    virtual std::string type() const { return "free"; } 
}; 

class TowerSquare : public MapSquare { 

    public: 
    TowerSquare(int x, int y, Tower* tower) : MapSquare(x, y), tower_(tower) {} 
    ~TowerSquare(){} 
    virtual bool free() const { return false; } 
    virtual bool occupied() const { return true; } 
    virtual std::string type() const { return "tower"; }

    Tower* GetTower() { return tower_; } 
    bool ContainsTower(Tower* tower) {
        if(tower_ == tower) return true;
        else return false;
    }


    private: 
    Tower* tower_; 
}; 

class EnemySquare : public MapSquare { 
    public: 
    EnemySquare(int x, int y) : MapSquare(x, y) {
        enemies_ = std::vector<Enemy*>();
        next_ = nullptr;
    } 
    ~EnemySquare(){} 
    virtual bool free() const { return false; } 
    virtual bool occupied() const { return true; } 
    virtual std::string type() const { return "enemy"; }
    std::vector<Enemy*> GetEnemies() { return enemies_; }
    void SetNext(EnemySquare* e_square) { next_ = e_square; }
    bool HasNext() { 
        if(this->next_ != nullptr) return true;
        else return false;
    }
    EnemySquare* GetNext() { return next_; }
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
            if(it == enemy) return it;
        }
        return nullptr;
    }

    bool ContainsEnemy(Enemy* enemy) const {
        if(this->GetEnemy(enemy) != nullptr) return true;
        else return false;
    }

    private:
    std::vector<Enemy*> enemies_;
    EnemySquare* next_;
}; 
