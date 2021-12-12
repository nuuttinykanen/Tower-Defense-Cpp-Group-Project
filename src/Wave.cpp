#include "Wave.hpp"
#include <stdexcept>
#include <iostream>


Wave::~Wave() {
    for(auto w : waveEnemies_) {
        delete(w);
    }
    waveEnemies_.clear();
}

void Wave::AddEnemyToWave(Enemy *enemy) {
    this->waveEnemies_.push_back(enemy);
}

void Wave::RemoveEnemyFromWave(Enemy* enemy) {
    for (auto e = waveEnemies_.begin(); e != waveEnemies_.end(); ++e) {
        if(*e == enemy) {
            waveEnemies_.erase(e);
            break;
        }
    }
}

Enemy& Wave::PopNext() {
    auto h = this->waveEnemies_.begin();
    if(h == this->waveEnemies_.end()) {
        throw std::invalid_argument("No next enemy found in wave!");
    };
    Enemy& en = *(*h);
    if(*h != nullptr) {
        this->RemoveEnemyFromWave(*h);
    }
    return en;
}

bool Wave::isEmpty() {
    if(this->waveEnemies_.empty()) return true;
    else return false;
}
