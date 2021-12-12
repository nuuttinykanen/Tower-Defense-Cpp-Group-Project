#include "menu_state.h"
#include "../Gui.h"
#include "game_state.h"
#include "level_select_state.h"
#include "../utils/sound_driver.h"


MenuState::MenuState(sf::RenderWindow& window, Gui* gui) : WindowState(window, gui) {

    // Generate buttons
    auto size = window_.getSize();
    auto startButton = new Button(sf::Vector2f (450, 50), sf::Vector2f(450, 125),
                                  "Start the latest save", this->GetFont(), 20, 10);

    buttons_[MenuButtonTarget::StartLatestSaveTarget] = startButton;

    auto levelSelectButton = new Button(sf::Vector2f (450, 50), sf::Vector2f(450, 225),
                                        "Level selector", this->GetFont(), 20, 85);

    buttons_[MenuButtonTarget::StartLevelSelectTarget] = levelSelectButton;

    auto quitButton = new Button(sf::Vector2f (450, 50), sf::Vector2f(450, 325),
                                 "Quit the game", this->GetFont(), 20, 100);
    buttons_[MenuButtonTarget::QuitTarget] = quitButton;

}
MenuState::~MenuState() {
    for (auto b : buttons_) {
        delete b.second;
    }
}

void MenuState::AdvanceState() {

}

void MenuState::DrawCurrentState() {

    for (auto b : buttons_) {
        b.second->draw(window_);
    }

}

void MenuState::PollEvents() {
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

                        case StartLatestSaveTarget:
                            gui_->getSoundDriver()->playSound(Hitmarker, 50);
                            StartLatestSave();
                            return;
                        case StartLevelSelectTarget:
                            StartLevelSelect();
                            return;
                        case QuitTarget:
                            Quit();
                            return;
                    }
                }
            } else if (event.mouseButton.button == 1) {

            }

        }



    }
}

void MenuState::StartLatestSave() {
    gui_->change_game_state(new GameState(window_, gui_, 0));

}

void MenuState::StartLevelSelect() {
    gui_->change_game_state(new LevelSelectState(window_, gui_));
}

void MenuState::Quit() {
    window_.close();
}
