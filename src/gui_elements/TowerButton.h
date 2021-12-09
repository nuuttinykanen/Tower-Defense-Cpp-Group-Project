#ifndef TOWER_DEFENSE_12_TOWERBUTTON_H
#define TOWER_DEFENSE_12_TOWERBUTTON_H

#include "Button.h"
// Doesn't extend class Button since they don't have a lot of functionality between them
class TowerButton {
public:
    TowerButton(Vector2f pos, sf::Sprite& towerSprite, sf::Font& font, int cost);
    ~TowerButton() = default;

    void draw(sf::RenderWindow &window, int currentMoney);

    bool contains(Vector2f pos);

private:
    RectangleShape box_;
    sf::Sprite& icon_;
    Vector2f pos_;
    Text text_;
    int cost_;
};


#endif //TOWER_DEFENSE_12_TOWERBUTTON_H
