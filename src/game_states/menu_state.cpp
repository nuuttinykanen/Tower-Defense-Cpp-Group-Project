#include "menu_state.h"
#include "../Gui.h"
#include "game_state.h"

MenuState::MenuState(sf::RenderWindow& window, Gui* gui) : WindowState(window, gui) {

    // Generate buttons
    auto size = window_.getSize();
    auto startButton = new Button(sf::Vector2f (425, 50), sf::Vector2f(500, 200),
                                  "Start a new game",this->getFont(), 20);

    buttons_[MenuButtonTarget::StartGame] = startButton;

    auto quitButton = new Button(sf::Vector2f (325, 50), sf::Vector2f(500, 300),
                                  "Quit the game",this->getFont(), 20);
    buttons_[MenuButtonTarget::Quit] = quitButton;

}
MenuState::~MenuState() {
    for (auto b : buttons_) {
        delete b.second;
    }
}

void MenuState::advance_state() {

}

void MenuState::draw_current_state() {

    for (auto b : buttons_) {
        b.second->draw(window_);
    }

}

void MenuState::poll_events() {
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

                        case StartGame:
                            start_game();
                            return;
                        case StartLevelSelect:
                            startLevelSelect();
                            return;
                        case Quit:
                            quit();
                            return;
                    }
                }
            } else if (event.mouseButton.button == 1) {

            }

        }



    }
}

void MenuState::start_game() {
    std::cout << "Starting the game!" << std::endl;
    gui_->change_game_state(new GameState(window_, gui_));
}

void MenuState::startLevelSelect() {
    std::cout << "Starting level select!" << std::endl;
}

void MenuState::quit() {
    window_.close();
}
