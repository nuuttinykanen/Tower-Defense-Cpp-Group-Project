#include "level_editor_state.h"

LevelEditorState::LevelEditorState(sf::RenderWindow &window, Gui* gui): WindowState(window, gui) {

}

void LevelEditorState::advance_state() {

}

void LevelEditorState::draw_current_state() {
    // TODO: This should come from some global object.
    sf::Font font;
    // Relative path from the cmake executable
    if (!font.loadFromFile("../src/assets/AtariClassicChunky-PxXP.ttf")) {
        //Error
        std::cout << "Error retrieving font file" << std::endl;
    }
    sf::Text text;
    text.setFont(font);
    text.setString("TODO: Level editor");
    text.setFillColor(sf::Color::White);
    window_.draw(text);

}
