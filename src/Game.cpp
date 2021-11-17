#include "Game.hpp"



void Game::SpawnEnemy(Enemy* enemy) {
    map_.PlaceEnemy(0, 0 ,enemy);
}

void Game::SpawnTower(Tower* tower, double x, double y) {

    map_.PlaceTower(x, y, tower);
    towers_.push_back(tower);
}

/*
LevelMap map_;
std::vector<Wave> enemyWaves_;
std::vector<Tower> towers_;
Player player_;
*/