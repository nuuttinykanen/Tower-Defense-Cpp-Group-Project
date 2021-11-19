#include "levelmap.hpp"
#include <vector>
#include "player.hpp"
#include "Wave.hpp"

class Game {

    public:

    Game(map = LevelMap(20), player = Player(), std::vector<Wave*> waves = std::vector<Wave*>()) : map_(map), player_(player)
    , enemyWaves_(waves){

        this->towers_ = player_.GetTowers();


    };


    void UpdateState();


    void SpawnEnemy(Enemy* enemy);

    void SpawnTower(Tower* tower, double x, double y);

    void StartWave(Wave v);



    private:
    LevelMap map_;
    std::vector<Wave*> enemyWaves_;
    std::vector<Tower*> towers_;
    Player player_;


};

