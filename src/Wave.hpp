 #include "enemy.hpp"
#include <vector>
#ifndef TOWER_DEFENSE_12_WAVE_HPP
#define TOWER_DEFENSE_12_WAVE_HPP


class Wave {

    public:
        Wave(std::vector<Enemy*> WaveEnemies = std::vector<Enemy*>()) :
        WaveEnemies_(WaveEnemies){};
        ~Wave();
        std::vector<Enemy*> getWaveEnemies() { return WaveEnemies_;};
        void AddEnemyToWave(Enemy* enemy);
        void RemoveEnemyFromWave(Enemy* enemy);


    private:
        std::vector<Enemy*> WaveEnemies_;
};


#endif //TOWER_DEFENSE_12_WAVE_HPP
