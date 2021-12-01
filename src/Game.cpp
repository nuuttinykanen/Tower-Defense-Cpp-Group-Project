#include "Game.hpp"


void Game::SpawnEnemy(Enemy* enemy) {
    this->map_.PlaceEnemy(0, 0 ,enemy);
    enemies_.push_back(enemy);
}

void Game::SpawnTower(Tower* tower, double x, double y) {
    this->player_.BuyTower(tower);
    this->map_.PlaceTower(x, y, tower);
    towers_.push_back(tower);
}


void Game::KillEnemy(Enemy *enemy) {
    this->map_.EraseEnemy(enemy);
    this->player_.GiveMoney(enemy->GetBounty());
    // Remove projectile
}


void Game::SellTower(Tower* tower) {
    this->player_.SellTower(tower);
    this->map_.EraseTower(tower);
}

// Start the first wave and then remove it from the vector
void Game::StartWave() {

    auto wave = enemyWaves_[0];
    auto enemyWave = wave->getWaveEnemies();
    enemyWaves_.erase(enemyWaves_.begin());
    for(auto e : enemyWave){
        SpawnEnemy(e);
    }
}


LevelMap &Game::GetMap() {
    return map_;
}

void Game::UpdateState() {

}
