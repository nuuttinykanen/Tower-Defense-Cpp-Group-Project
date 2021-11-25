#include "levelmap.hpp"
#include <vector>
#include "player.hpp"
#include "Wave.hpp"
#include "projectile.hpp"
class Game {

    public:

    Game(map = LevelMap(20), player = Player(), std::vector<Wave*> waves = std::vector<Wave*>()) : map_(map), player_(player)
    , enemyWaves_(waves){

        this->towers_ = player_.GetTowers();
        this->enemies_ = map_.GetEnemies();
        this->projectiles_ = map_.GetProjectiles();
    };


    void UpdateState();


    void SpawnEnemy(Enemy* enemy);

    void SpawnTower(Tower* tower, double x, double y);

    void KillEnemy(Enemy* enemy);

    void SellTower(Tower* tower);

    void StartWave(Wave v);



    private:
    LevelMap map_;
    std::vector<Wave*> enemyWaves_;
    std::vector<Tower*> towers_;
    std::vector<Enemy*> enemies_;
    std::vector<Projectile*> projectiles_;
    Player player_;


};

