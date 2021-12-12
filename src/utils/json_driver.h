#ifndef TOWER_DEFENSE_12_JSON_DRIVER_H
#define TOWER_DEFENSE_12_JSON_DRIVER_H

#include "../../libs/json/json.h"
#include "../Game.hpp"
#include "../levelmap.hpp"
#include "../Wave.hpp"
#include "../enemy.hpp"

#include <map>
#include "fstream"
#include "iostream"
#include "utility"
#include <algorithm>


using std::make_pair;
using std::pair;


class JSON {
public:
    static bool LatestSaveExists();
    static int GetNumberOfLevels();
    static LevelMap* LoadLevelMap(int index);
    static std::vector<Wave*> LoadWaves(int index);
    static void SaveCurrentGame(Game* game, int levelNumber);
    static Game* LoadLatestSave();
};



#endif //TOWER_DEFENSE_12_JSON_DRIVER_H
