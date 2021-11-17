#include "levelmap.hpp"
#include <vector>
#include "player.hpp"

class Game {

    public:

    Game(map = LevelMap(20), player = Player()) : map_(map), player_(player) {

        this->towers_ = player_.GetTowers();
    };


    void UpdateState();


    void SpawnEnemy(Enemy* enemy);

    void SpawnTower(Tower* tower, double x, double y);

    void StartWave(Wave v);



    private:
    LevelMap map_;
    //std::vector<Wave> enemyWaves_;
    std::vector<Tower*> towers_;
    Player player_;


};

