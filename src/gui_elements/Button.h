#ifndef TOWER_DEFENSE_12_BUTTON_H
#define TOWER_DEFENSE_12_BUTTON_H
#include <SFML/Graphics.hpp>
#include <iostream>

class WindowState;
class MenuState;

using sf::Color;
using sf::Vector2f;
using sf::RectangleShape;
using sf::Text;
using std::string;

// Generic button with text inside it
class Button {
public:
    Button(Vector2f size, Vector2f pos, string text, sf::Font& font, int fontsize,
           float textOffsetX = 0, float textOffsetY = 10,
           Color boxColor = Color::White,
           Color textColor = Color::Black);
    ~Button() = default;

    void draw(sf::RenderWindow &window);

    bool contains(Vector2f pos);

private:
    Vector2f size_;
    Vector2f pos_;
    Color boxColor_;
    Color textColor_;
    RectangleShape box_;
    Text text_;
};


#endif //TOWER_DEFENSE_12_BUTTON_H
