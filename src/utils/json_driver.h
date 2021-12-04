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


class JSON {
public:
    static void test();
    static int getNumberOfLevels();
    static LevelMap* loadLevelMap(int index);

};



#endif //TOWER_DEFENSE_12_JSON_DRIVER_H
