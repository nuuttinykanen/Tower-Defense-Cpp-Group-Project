#include "../Gui.h"
#include "game_state.h"
#include "menu_state.h"

GameState::GameState(sf::RenderWindow &window, Gui* gui) : WindowState(window, gui) {
    // Generate buttons
    auto startButton = new Button(sf::Vector2f (325, 50), sf::Vector2f(100, 200),
                                  "Quit to menu",this->getFont(), 20);

    buttons_[GameButtonTarget::QuitToMenu] = startButton;
}
GameState::~GameState() {
    for (auto b : buttons_) {
        delete b.second;
    }
}

void GameState::advance_state() {

}

void GameState::draw_current_state() {
    for (auto b : buttons_) {
        b.second->draw(window_);
    }

}

void GameState::poll_events() {
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
                    // Move to next one if this button is not clicked
                    if (!b.second->contains(mouse_pos)) continue;
                    switch (b.first) {

                        case QuitToMenu:
                            quitToMenu();
                            return;
                    }
                }
            } else if (event.mouseButton.button == 1) {

            }

        }



    }
}

void GameState::quitToMenu() {
    std::cout << "Quitting to menu!" << std::endl;
    gui_->change_game_state(new MenuState(window_, gui_));
}
