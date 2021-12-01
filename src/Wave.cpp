#include "Wave.hpp"

void Wave::AddEnemyToWave(Enemy *enemy) {

    this->WaveEnemies_.push_back(enemy);
}

void Wave::RemoveEnemyFromWave(Enemy* enemy) {

    for (auto e = WaveEnemies_.begin(); e != WaveEnemies_.end(); e++) {
        if (*e == enemy) WaveEnemies_.erase(e);
    }
}

