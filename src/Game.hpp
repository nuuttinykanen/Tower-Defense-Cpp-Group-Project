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
        this->gameEnd_ = false;
        this->enemies_ = map_.GetEnemies();
        this->projectiles_ = map_.GetProjectiles();
        this->waveInProgress_ = false;
        this->waveNum_ = 1;
        this->moveCounter_ = 0;
        this->moveLimit_ = 10;
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

    void EndWave();

    unsigned int GetTotalWaveCount();

    bool ifWaveInProgress();

    Wave* GetCurrentWave();

    void ProcessEnemies();

    void ProcessAttackTowers();

    private:
    LevelMap& map_;
    Player& player_;
    std::vector<Wave*> enemyWaves_;
    unsigned int waveNum_;
    unsigned int moveCounter_;
    unsigned int moveLimit_;
    std::vector<Tower*> towers_;

    std::vector<Enemy*> enemies_;
    std::vector<Projectile*> projectiles_;
    bool gameEnd_;
    bool waveInProgress_;

};

