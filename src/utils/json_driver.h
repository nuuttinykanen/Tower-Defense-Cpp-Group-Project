#ifndef TOWER_DEFENSE_12_JSON_DRIVER_H
#define TOWER_DEFENSE_12_JSON_DRIVER_H

#include "../../libs/json/json.h"
#include "../levelmap.hpp"
#include <map>
#include "fstream"
#include "iostream"
#include "utility"

using std::make_pair;
using std::pair;

// Maps each map index to a save file name

class JSON {
public:
    static void test();

    static LevelMap* loadLevelMap(int index);
};



#endif //TOWER_DEFENSE_12_JSON_DRIVER_H
