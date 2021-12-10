
#include "Gui.h"
#include "game_states/window_state.h"
#include "game_states/menu_state.h"
#define GAME_TITLE "Tower defense"


Gui::Gui(int width, int height)
    : screen_width_(width), screen_height_(height),
    window_(sf::RenderWindow(sf::VideoMode(width, height), GAME_TITLE, sf::Style::Titlebar | sf::Style::Close)),
    current_state_(nullptr),
    globalObjects_(new GlobalObjects())
{
    window_.setFramerateLimit(60);
    window_.setKeyRepeatEnabled(false);
    ///window_.
    change_game_state(new MenuState(window_, this));
    start_main_loop();
}

void Gui::start_main_loop() {

    while (window_.isOpen())
    {

        current_state_->poll_events();
        current_state_->draw_window();

    }
}

void Gui::change_game_state(WindowState* new_state) {
    std::cout << "done creating2" << std::endl;

    delete current_state_;
    std::cout << "done creating3" << std::endl;

    current_state_ = new_state;
    std::cout << "done creating4" << std::endl;

}

