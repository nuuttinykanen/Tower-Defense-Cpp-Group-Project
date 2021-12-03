#ifndef TOWER_DEFENSE_12_GLOBALOBJECTS_H
#define TOWER_DEFENSE_12_GLOBALOBJECTS_H
#include "SFML/Graphics.hpp"
#include <iostream>
// Contains fonts, sprites, etc. so they don`t have to be initalized everytime
class GlobalObjects {
public:
    GlobalObjects();
    sf::Font& getFont() { return font_; };

    sf::Sprite& getEnemySprite(float scaledBy = 1);
    sf::Sprite& getPurpleEnemySprite(float scaledBy = 1);

    sf::Sprite& getFreeSquareSprite(float scaledBy = 1);
    sf::Sprite& getEnemySquareSprite(float scaledBy = 1);
    sf::Sprite& getTowerSquareSprite(float scaledBy = 1);

private:
    sf::Font font_;
    sf::Texture enemyTexture_;
    sf::Texture purpleEnemyTexture_;
    sf::Texture freeSquareTexture_;
    sf::Texture enemySquareTexture_;
    sf::Texture towerSquareTexture_;
    sf::Sprite enemySprite_;
    sf::Sprite purpleEnemySprite_;
    sf::Sprite freeSquareSprite_;
    sf::Sprite enemySquareSprite_;
    sf::Sprite towerSquareSprite_;
};


#endif //TOWER_DEFENSE_12_GLOBALOBJECTS_H
