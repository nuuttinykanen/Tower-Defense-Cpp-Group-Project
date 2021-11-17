#include "Game.hpp"



void Game::SpawnEnemy(Enemy* enemy) {
    map_.PlaceEnemy(0, 0 ,enemy);
}

void Game::SpawnTower(Tower* tower, double x, double y) {

    map_.PlaceTower(x, y, tower);
    towers_.push_back(tower);
}

void Game::StartWave(Wave v) {
    for(auto e : v){
        SpawnEnemy(e);
    }
}