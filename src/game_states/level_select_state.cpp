#include "level_select_state.h"


LevelSelectState::LevelSelectState(sf::RenderWindow &window, Gui* gui): WindowState(window, gui) {
    GenerateButtons();
}

void LevelSelectState::AdvanceState() {

}

void LevelSelectState::DrawCurrentState() {
    for (auto b : buttons_) {
        b.second->draw(window_);
    }
}

void LevelSelectState::PollEvents() {
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
                    gui_->getSoundDriver()->playSound(SelectSound, 50);
                    if (!b.second->contains(mouse_pos)) continue;

                    switch (b.first) {
                        case -1:{
                            auto menu = new MenuState(window_, gui_);
                            gui_->change_game_state(menu);
                            return;
                        }
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

void LevelSelectState::GenerateButtons() {
    auto latestSaveButton = new Button(sf::Vector2f(350, 50), sf::Vector2f(475, 100),
                                       "Load latest save", GetFont(), 20, 15);
    buttons_[0] = latestSaveButton;

    int y = 0;
    int x = 0;
    // Draw buttons in a 4xX grid
    for (int i = 1; i <= JSON::getNumberOfLevels() ; i++) {
        auto button = new Button(sf::Vector2f(50, 50), sf::Vector2f(475 + 100 * x, 200 + 100 * y),
                                 std::to_string(i), GetFont(), 20, 15);
        buttons_[i] = button;
        x++;
        if (i % 4 == 0)  {
            y++;
            x = 0;
        }
        if (i == JSON::getNumberOfLevels()) {
            auto backToMenuButton = new Button(sf::Vector2f(350, 50), sf::Vector2f(475, 300 + 100 * y),
                                               "Back to main menu", GetFont(), 20, 10);
            buttons_[-1] = backToMenuButton;
        }
    }
}
