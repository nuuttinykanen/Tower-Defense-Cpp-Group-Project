#include "level_select_state.h"


LevelSelectState::LevelSelectState(sf::RenderWindow &window, Gui* gui): WindowState(window, gui) {
    JSON::loadLevelMap(1);
}

void LevelSelectState::advance_state() {

}

void LevelSelectState::draw_current_state() {
    // TODO: This should come from some global object.
    sf::Font font;
    // Relative path from the cmake executable
    if (!font.loadFromFile("../src/assets/AtariClassicChunky-PxXP.ttf")) {
        //Error
        std::cout << "Error retrieving font file" << std::endl;
    }
    sf::Text text;
    text.setFont(font);
    text.setString("TODO: Level selector");
    text.setFillColor(sf::Color::White);
    window_.draw(text);

}

void LevelSelectState::poll_events() {
    sf::Event event{};


    while (window_.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window_.close();

        // 0 -> primary click, 1-> secondary
        if (event.type == sf::Event::MouseButtonReleased) {
            if (event.mouseButton.button == 0) {
                auto mouse_pos = window_.mapPixelToCoords(sf::Mouse::getPosition(window_));

            } else if (event.mouseButton.button == 1) {

            }

        }



    }
}
