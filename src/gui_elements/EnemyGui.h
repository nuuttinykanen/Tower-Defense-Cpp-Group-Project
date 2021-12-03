
#ifndef TOWER_DEFENSE_12_ENEMYGUI_H
#define TOWER_DEFENSE_12_ENEMYGUI_H
#include <SFML/Graphics.hpp>

class EnemyGui {
public:
    EnemyGui(sf::Sprite& towerSprite);
    ~EnemyGui() = default;
    sf::Sprite& GetSprite();
private:
    sf::Sprite& sprite_;
};

#endif //TOWER_DEFENSE_12_ENEMYGUI_H
