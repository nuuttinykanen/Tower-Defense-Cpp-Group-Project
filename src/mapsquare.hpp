#include "tower.hpp"
class MapSquare {
    public:
    MapSquare(int x, int y) : x_(x), y_(y) { }
    ~MapSquare(){} 
    virtual bool free() = 0;
    virtual bool occupied() = 0;
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
}; 

class TowerSquare : public MapSquare { 

    public: 
    TowerSquare(int x, int y, Tower tower) : MapSquare(x, y), tower_(tower) {} 
    ~TowerSquare(){} 
    virtual bool free() { return false; } 
    virtual bool occupied() { return true; } 
    Tower& getTower() { return tower_; } 

    private: 
    Tower tower_; 
}; 

class EnemyPathSquare : public MapSquare { 
    public: 
    EnemyPathSquare(int x, int y) : MapSquare(x, y){} 
    ~EnemyPathSquare(){} 
    virtual bool free() { return false; } 
    virtual bool occupied() { return false; } 
}; 

class EnemySquare : public EnemyPathSquare { 
    public: 
    EnemySquare(int x, int y, Enemy enemy) : EnemyPathSquare(x, y), enemy_(enemy){} 
    ~EnemySquare(){} 
    virtual bool free() { return false; } 
    virtual bool occupied() { return true; }
    Enemy& getEnemy() = { return enemy_ }
    private:
    Enemy enemy_;
}; 