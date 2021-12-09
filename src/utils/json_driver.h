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
    static bool latestSaveExists();
    static int getNumberOfLevels();
    static LevelMap* loadLevelMap(int index);
    static std::vector<Wave*> loadWaves(int index);
    static void saveCurrentGame(Game* game, int levelNumber);
    static Game* loadLatestSave();
};



#endif //TOWER_DEFENSE_12_JSON_DRIVER_H
