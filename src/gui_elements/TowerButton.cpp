#include "TowerButton.h"

TowerButton::TowerButton(Vector2f pos, sf::Sprite& towerSprite, sf::Font &font, int cost)  :
        box_(RectangleShape(Vector2f(90, 90))),
        icon_(towerSprite),
        pos_(pos),
        cost_(cost)
{
    text_.setCharacterSize(10);
    text_.setFont(font);
    text_.setString(std::to_string(cost) + "$");
    text_.setOutlineThickness(2);
    text_.setOutlineColor(Color::Black);
    box_.setPosition(pos);
    box_.setOutlineColor(Color::Black);
    box_.setOutlineThickness(5);
    box_.setFillColor(Color::White);
}

void TowerButton::draw(sf::RenderWindow &window, int currentMoney) {
    window.draw(box_);

    icon_.setPosition(pos_.x + 15, pos_.y + 10);
    icon_.setScale(3, 3);
    window.draw(icon_);

    text_.setPosition(pos_.x + 30, pos_.y + 75);
    if (currentMoney >= cost_) {
        text_.setFillColor(Color(133,187, 101));
    } else {
        text_.setFillColor(Color::Red);
    }
    window.draw(text_);


}

bool TowerButton::contains(Vector2f pos) {
    if (box_.getGlobalBounds().contains(pos)) {
        return true;
    } else {
        return false;
    }
}
