#include "Wave.hpp"

void Wave::AddEnemyToWave(Enemy *enemy) {

    this->WaveEnemies_.push_back(enemy);
}

void Wave::RemoveEnemyFromWave(Enemy* enemy){

    this->WaveEnemies_.erase(std::remove(this->WaveEnemies_.begin(), this->WaveEnemies_.end(), enemy), this->WaveEnemies_.end());
}

