#include "Button.h"

Button::Button(Vector2f size, Vector2f pos, string text, sf::Font& font, int fontsize,
        Color boxColor, Color textColor)
: size_(size), pos_(pos), boxColor_(boxColor), textColor_(textColor),
box_(RectangleShape(size)){
    box_.setPosition(pos);
    box_.setFillColor(boxColor);
    text_.setFont(font);
    text_.setCharacterSize(fontsize);
    text_.setString(text);
    text_.setFillColor(textColor);
    text_.setString(text);
    text_.setPosition(pos.x, pos.y + 10);
}

void Button::draw(sf::RenderWindow &window) {
    window.draw(box_);
    window.draw(text_);
}

bool Button::contains(Vector2f pos) {
    if (box_.getGlobalBounds().contains(pos)) {
        return true;
    } else {
        return false;
    }
}
