#include "Game.hpp"



void Game::SpawnEnemy(Enemy* enemy) {
    this->map_.PlaceEnemy(0, 0 ,enemy);
    enemies_.push_back(enemy);
}

void Game::SpawnTower(Tower* tower, double x, double y) {

    this->map_.PlaceTower(x, y, tower);
    towers_.push_back(tower);
}

void Game::KillEnemy(Enemy *enemy) {
    this->map_.EraseEnemy(enemy);
    this->player_.GiveMoney(enemy->GetBounty());
}

void Game::SellTower(Tower* tower) {
    this->player_.SellTower(tower);
    this->map_.EraseTower(tower);
}


void Game::StartWave(Wave v) {
    for(auto e : v){
        SpawnEnemy(e);
    }
}



