#ifndef TOWER_DEFENSE_12_GAME_H
#define TOWER_DEFENSE_12_GAME_H


#include "levelmap.hpp"
#include <vector>
#include "player.hpp"
#include "Wave.hpp"
#include "projectile.hpp"
class Game {

    public:

    Game(LevelMap& map, Player& player, std::vector<Wave*> waves) : map_(map), player_(player)
    , enemyWaves_(waves), totalWaveCount_(waves.size()) {

        this->towers_ = map_.GetTowers();
        this->gameEnd_ = false;
        this->enemies_ = map_.GetEnemies();
        this->projectiles_ = map_.GetProjectiles();
        this->waveInProgress_ = false;
        this->waveNum_ = 1;
        this->enemyMoveCounter_ = 0;
        this->projectileMoveCounter_ = 0;
        this->enemyMoveLimit_ = 15;
        this->projectileMoveLimit_ = 3;
        this->waveSpawned_ = false;
    };

    ~Game();

    LevelMap& GetMap();

    Player& GetPlayer() {return player_;}

    unsigned int GetWaveNumber() {return waveNum_;}

    void SetWaveNumber(unsigned int newWaveNumber);

    void UpdateState();

    void EndGame();

    void SpawnEnemy(Enemy* enemy);

    void SpawnTower(Tower* tower, double x, double y);

    void KillEnemy(Enemy* enemy);

    void SellTower(TowerSquare* towerSquare);

    void StartWave();

    void EndWave();

    unsigned int GetTotalWaveCount() {return totalWaveCount_;};

    int GetStartOfWaveMoney() {return startOfWaveMoney_;}

    unsigned int GetStartOfWaveHealth() {return startOfWaveHealth_;}

    bool isWaveInProgress();

    Wave* GetCurrentWave();

    void ProcessEnemies();

    void ProcessTowers();

    bool isGameOver() const { return gameEnd_;}
    void TakeDamage(Enemy* enemy);

    private:
    LevelMap& map_;
    Player& player_;
    // Need to keep track of how much money the player has at the start of an wave for the save file
    int startOfWaveMoney_;
    unsigned int startOfWaveHealth_;
    std::vector<Wave*> enemyWaves_;
    unsigned int waveNum_;
    unsigned int totalWaveCount_;
    unsigned int enemyMoveCounter_;
    unsigned int enemyMoveLimit_;
    unsigned int projectileMoveCounter_;
    unsigned int projectileMoveLimit_;
    std::vector<Tower*> towers_;

    std::vector<Enemy*> enemies_;
    std::vector<Projectile*> projectiles_;
    bool gameEnd_;
    bool waveInProgress_;
    bool waveSpawned_;

};

#endif
