#ifndef MAPSQUARE_HPP
#define MAPSQUARE_HPP
#include <string>
#include <vector>
#include "enemy.hpp"
#include "towers/tower.hpp"
class MapSquare {
    public:
    MapSquare(int x, int y) : x_(x), y_(y) { }
    virtual ~MapSquare() = default;
    virtual bool free() const = 0;
    virtual std::string GetType() const = 0;
    int GetX() const;
    int GetY() const;
    private: 
    int const x_;
    int const y_;
};

class FreeSquare : public MapSquare {
    public: 
    FreeSquare(int x, int y) : MapSquare(x, y){} 
    ~FreeSquare(){} 
    virtual bool free() const;
    virtual std::string GetType() const;
};

class EnemySquare : public MapSquare { 
    public: 
    EnemySquare(int x, int y) : MapSquare(x, y) {
        enemies_ = std::vector<Enemy*>();
        next_ = nullptr;
        previous_ = nullptr;
        number_ = -1;
    }

    ~EnemySquare(){
        for(auto en : enemies_) {
            delete(en);
        }
    }

    virtual bool free() const;
    virtual std::string GetType() const;
    std::vector<Enemy*> GetEnemies();
    void SetNext(EnemySquare* e_square);
    bool HasNext();
    EnemySquare* GetNext();
    void SetPrevious(EnemySquare* e_square);
    EnemySquare* GetPrevious();
    void AddEnemy(Enemy* enemy);
    bool RemoveEnemy(Enemy* enemy);
    bool ContainsEnemies() const;
    Enemy* GetEnemy(Enemy* enemy) const;

    bool ContainsEnemy(Enemy* enemy) const;
    unsigned int GetNumber() const;
    void SetNumber(unsigned int number);

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
    ~TowerSquare(){ delete tower_; }
    virtual bool free() const;
    virtual std::string GetType() const;

    Tower* GetTower();
    bool ContainsTower(Tower* tower);
    std::vector<EnemySquare*> EnemySquaresInRange();
    void AddToEnemiesInRange(EnemySquare* es);

private:
    Tower* tower_;
    std::vector<EnemySquare*> enemySquaresInRange_;
};
#endif