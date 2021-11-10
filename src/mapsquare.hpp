#include "tower.hpp"
#include <string>
#include <vector>
#include "enemy.hpp"
class MapSquare {
    public:
    MapSquare(int x, int y) : x_(x), y_(y) { }
    ~MapSquare(){} 
    virtual bool free() = 0;
    virtual bool occupied() = 0;
    virtual std::string type() = 0;
    private: 
    int x_;
    int y_;
};

class FreeSquare : public MapSquare { 

    public: 
    FreeSquare(int x, int y) : MapSquare(x, y){} 
    ~FreeSquare(){} 
    virtual bool free() { return true; } 
    virtual bool occupied() { return false; }
    virtual std::string type() { return "free"; }
}; 

class TowerSquare : public MapSquare { 

    public: 
    TowerSquare(int x, int y, Tower tower) : MapSquare(x, y), tower_(tower) {} 
    ~TowerSquare(){} 
    virtual bool free() { return false; } 
    virtual bool occupied() { return true; } 
    Tower& getTower() { return tower_; } 
    virtual std::string type() { return "tower"; }

    private: 
    Tower tower_; 
}; 

class EnemyPathSquare : public MapSquare { 
    public: 
    EnemyPathSquare(int x, int y) : MapSquare(x, y){} 
    ~EnemyPathSquare(){} 
    virtual bool free() { return false; } 
    virtual bool occupied() { return false; } 
    virtual std::string type() { return "epath"; }
}; 

class EnemySquare : public EnemyPathSquare { 
    public: 
    EnemySquare(int x, int y, std::vector<Enemy*> enemies) : EnemyPathSquare(x, y), enemies_(enemies){} 
    ~EnemySquare(){} 
    virtual bool free() { return false; } 
    virtual bool occupied() { return true; }
    std::vector<Enemy*> getEnemies() { return enemies_; }
    virtual std::string type() { return "enemy"; }
    private:
    std::vector<Enemy*> enemies_;
}; 
