
#include "gui.h"
#include "game_states/window_state.h"
#include "game_states/menu_state.h"
#define GAME_TITLE "Bloonless tower defence"


Gui::Gui(int width, int height)
    : screen_width_(width), screen_height_(height),
      window_(sf::RenderWindow(sf::VideoMode(width, height), GAME_TITLE, sf::Style::Titlebar | sf::Style::Close)),
      current_state_(nullptr),
      global_objects_(new GlobalObjects()),
      sound_(new SoundDriver())
{
    window_.setFramerateLimit(60);
    window_.setKeyRepeatEnabled(false);
    ///window_.
    ChangeGameState(new MenuState(window_, this));
    StartMainLoop();
}

void Gui::StartMainLoop() {

    while (window_.isOpen())
    {

        current_state_->PollEvents();
        current_state_->DrawWindow();


    }
}

void Gui::ChangeGameState(WindowState* new_state) {

    delete current_state_;

    current_state_ = new_state;

}

