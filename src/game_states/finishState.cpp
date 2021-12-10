#include "finishState.h"
#include "game_state.h"
#include "menu_state.h"

FinishState::FinishState(sf::RenderWindow &window, Gui* gui, int levelNumber): levelNumber_(levelNumber), WindowState(window, gui) {

    text_.setFont(getFont());
    text_.setCharacterSize(30);
    text_.setString("Congratulations for finishing lvl: " + std::to_string(levelNumber) + "!" );
    text_.setPosition(125, 75);
    generate_buttons();
}

FinishState::~FinishState() {
    for (auto b : buttons_){
        delete b.second;
    }
}

void FinishState::advance_state() {

}

void FinishState::draw_current_state() {

    for (auto b : buttons_) {
        b.second->draw(window_);
    }
    window_.draw(text_);
}

void FinishState::poll_events() {
    sf::Event event{};


    while (window_.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window_.close();

        // 0 -> primary click, 1-> secondary
        if (event.type == sf::Event::MouseButtonReleased) {
            if (event.mouseButton.button == 0) {
                auto mouse_pos = window_.mapPixelToCoords(sf::Mouse::getPosition(window_));

                for (auto b: buttons_) {
                    if (!b.second->contains(mouse_pos)) continue;

                    switch (b.first) {
                        case PlayAgain: {
                            auto gS = new GameState(window_, gui_, levelNumber_);
                            gui_->change_game_state(gS);
                            return;
                        }
                        case MainMenu: {
                            auto mS = new MenuState(window_, gui_);
                            gui_->change_game_state(mS);
                            return;
                        }
                    }
                }

            } else if (event.mouseButton.button == 1) {

            }

        }
    }
}
    void FinishState::generate_buttons() {
        auto maineMenuButton = new Button(sf::Vector2f(350, 50), sf::Vector2f(475, 200),
                                          "Back to main menu", getFont(), 20, 10);
        buttons_[FinishButtonTarget::MainMenu] = maineMenuButton;

        auto playAgainButton = new Button(sf::Vector2f(350, 50), sf::Vector2f(475, 300),
                                          "Play again!", getFont(), 20, 50);
        buttons_[FinishButtonTarget::PlayAgain] = playAgainButton;
    }

