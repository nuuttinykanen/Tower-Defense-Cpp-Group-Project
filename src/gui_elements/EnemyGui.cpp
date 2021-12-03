#include "EnemyGui.h"

EnemyGui::EnemyGui(sf::Sprite& sprite) : sprite_(sprite) { }

sf::Sprite& EnemyGui::GetSprite() {
    return sprite_;
}