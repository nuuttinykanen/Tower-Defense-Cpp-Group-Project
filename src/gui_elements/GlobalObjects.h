#ifndef TOWER_DEFENSE_12_GLOBALOBJECTS_H
#define TOWER_DEFENSE_12_GLOBALOBJECTS_H
#include "SFML/Graphics.hpp"
#include <iostream>
// Contains fonts, sprites, etc. so they don`t have to be initalized everytime
class GlobalObjects {
public:
    GlobalObjects();
    sf::Font& getFont() { return font_; };
private:
    sf::Font font_;
};


#endif //TOWER_DEFENSE_12_GLOBALOBJECTS_H
