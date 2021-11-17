#include "Wave.hpp"

void Wave::AddEnemyToWave(Enemy *enemy) {

    this->WaveEnemies_.push_back(enemy);
}