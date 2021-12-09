#include "level_select_state.h"


LevelSelectState::LevelSelectState(sf::RenderWindow &window, Gui* gui): WindowState(window, gui) {
    generateButtons();
    JSON::loadLevelMap(1);
    int y = 0;
    int x = 0;


    auto latestSaveButton = new Button(sf::Vector2f(350, 50), sf::Vector2f(475, 100),
                                       "Load latest save", getFont(), 20, 15);
    buttons_[0] = latestSaveButton;

    // Draw buttons in a 4xX grid
    for (int i = 1; i <= JSON::getNumberOfLevels() ; i++) {
        auto button = new Button(sf::Vector2f(50, 50), sf::Vector2f(475 + 100 * x, 200 + 100 * y),
                                 std::to_string(i), getFont(), 20, 15);
        buttons_[i] = button;
        x++;
        if (i % 4 == 0)  {
            y++;
            x = 0;
        }
    }
}

void LevelSelectState::advance_state() {

}

void LevelSelectState::draw_current_state() {
    for (auto b : buttons_) {
        b.second->draw(window_);
    }
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

                for (auto b : buttons_) {
                    if (!b.second->contains(mouse_pos)) continue;

                    switch (b.first) {
                        case 0: {
                            auto game = new GameState(window_, gui_, 0);
                            gui_->change_game_state(game);
                            return;
                        }
                        default: {
                            auto game = new GameState(window_, gui_, b.first);
                            gui_->change_game_state(game);
                            return;
                        }
                    }
                }

            } else if (event.mouseButton.button == 1) {

            }

        }



    }
}

void LevelSelectState::generateButtons() {

}
