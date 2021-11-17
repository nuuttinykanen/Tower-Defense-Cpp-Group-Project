#include "game_state.h"

GameState::GameState(sf::RenderWindow &window) : WindowState(window) {

}

void GameState::advance_state() {

}

void GameState::draw_current_state() {
    // TODO: This should come from some global object.
    sf::Font font;
    // Relative path from the cmake executable
    if (!font.loadFromFile("../src/assets/AtariClassicChunky-PxXP.ttf")) {
        //Error
        std::cout << "Error retrieving font file" << std::endl;
    }
    sf::Text text;
    text.setFont(font);
    text.setString("TODO: Game");
    text.setFillColor(sf::Color::White);
    window_.draw(text);

}
