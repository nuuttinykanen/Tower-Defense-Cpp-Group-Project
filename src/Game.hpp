#include "levelmap.hpp"
#include <vector>


class Game {

    public:

    Game() : map_(LevelMap(20)), towers_(std::vector<Tower*>()), enemyWaves_(std::vector<Wave>())
    , player_(Player()) {};


    void UpdateState();


    void SpawnEnemy(Enemy* enemy);

    void SpawnTower(Tower* tower, double x, double y);

    void StartWave(Wave v);

    void StartGame();




    private:
    LevelMap map_;
    std::vector<Wave> enemyWaves_;
    std::vector<Tower*> towers_;
    Player player_;


};

