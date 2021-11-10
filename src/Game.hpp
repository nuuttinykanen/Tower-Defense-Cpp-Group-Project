#include "levelmap.hpp"
#include <vector>

class Game {

    public:

    Game()  {
        map_ = new LevelMap(...);
        player_ = new Player(....);
        towers_ = std::vector<Tower>();
        enemyWaves_ = std::vector<Wave>();
    }

    void UpdateState(){

        //Update enemies, projectiles and towers in _map (spawn, move, take damage etc..)
        // ----->
        //Update state locally according to map_, GUI renders accordingly ?
        // ----->


    }

    void Run() {

        // While game in progress {
        // sleep(..)
        // this->UpdateState();
        //
        // }
    }

    // Add enemy or Tower to map_?
    void SpawnEnemy(Enemy enemy);

    void SpawnTower(Tower tower, double x, double y);

    void StartWave(Wave v){

        // SpawnEnemy(Enemy enemy); for each enemy in the wave, with a delay?
    }


    private:
    LevelMap map_;
    std::vector<Wave> enemyWaves_;
    std::vector<Tower> towers_;
    Player player_;


};

