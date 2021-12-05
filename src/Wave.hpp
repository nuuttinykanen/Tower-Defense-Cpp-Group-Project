 #include "enemy.hpp"
#include <vector>
#ifndef TOWER_DEFENSE_12_WAVE_HPP
#define TOWER_DEFENSE_12_WAVE_HPP


class Wave {

    public:
        Wave(std::vector<Enemy*> waveEnemies = std::vector<Enemy*>()) :waveEnemies_(waveEnemies){};
        ~Wave();
        std::vector<Enemy*> getWaveEnemies() { return waveEnemies_;};
        void AddEnemyToWave(Enemy* enemy);
        void RemoveEnemyFromWave(Enemy* enemy);
        Enemy& PopNext();
        bool isEmpty();

    private:
        std::vector<Enemy*> waveEnemies_;
};


#endif //TOWER_DEFENSE_12_WAVE_HPP
