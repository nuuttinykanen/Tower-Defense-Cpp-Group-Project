#include "levelmap.hpp"
#include <vector>
#include "player.hpp"
#include "Wave.hpp"
#include "projectile.hpp"
class Game {

    public:

    Game(LevelMap& map, Player& player, std::vector<Wave*> waves) : map_(map), player_(player)
    , enemyWaves_(waves){

        this->towers_ = player_.GetTowers();
        this->GameEnd_ = false;
        this->enemies_ = map_.GetEnemies();
        this->projectiles_ = map_.GetProjectiles();
        this->WaveInProgress_ = false;
    };

    ~Game();

    LevelMap& GetMap();

    void UpdateState();

    void EndGame();

    void SpawnEnemy(Enemy* enemy);

    void SpawnTower(Tower* tower, double x, double y);

    void KillEnemy(Enemy* enemy);

    void SellTower(Tower* tower);

    void StartWave();

    int GetWaveCount() { return enemyWaves_.size(); };

    private:
    LevelMap& map_;
    Player& player_;
    std::vector<Wave*> enemyWaves_;
    std::vector<Tower*> towers_;

    std::vector<Enemy*> enemies_;
    std::vector<Projectile*> projectiles_;
    bool GameEnd_;
    bool WaveInProgress_;

};

