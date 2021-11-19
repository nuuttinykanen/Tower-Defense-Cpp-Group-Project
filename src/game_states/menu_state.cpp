#include "menu_state.h"
#include "../Gui.h"

MenuState::MenuState(sf::RenderWindow& window, Gui* gui) : WindowState(window, gui) {

}

void MenuState::advance_state() {

}

void MenuState::draw_current_state() {
    // TODO: This should come from some global object.
    sf::Font font;
    // Relative path from the cmake executable
    if (!font.loadFromFile("../src/assets/AtariClassicChunky-PxXP.ttf")) {
        //Error
        std::cout << "Error retrieving font file" << std::endl;
        return;
    }
    sf::Text text;
    text.setFont(font);
    text.setString("TODO: Menu");
    text.setFillColor(sf::Color::White);
    window_.draw(text);

    int width = gui_->get_screen_width();
    int height = gui_->get_screen_height();

    sf::RectangleShape rec = sf::RectangleShape(sf::Vector2f(120, 50));
    window_.draw(rec);

}
