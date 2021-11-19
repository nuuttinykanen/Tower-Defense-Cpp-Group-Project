
#include "Gui.h"
#include "game_states/window_state.h"
#include "game_states/menu_state.h"
#define GAME_TITLE "Tower defense"


Gui::Gui(int width, int height)
    : screen_width_(width), screen_height_(height),
    window_(sf::RenderWindow(sf::VideoMode(width, height), GAME_TITLE)),
    current_state_(nullptr)

{
    window_.setFramerateLimit(60);
    change_game_state(new MenuState(window_, this));
    start_main_loop();
}

void Gui::start_main_loop() {

    while (window_.isOpen())
    {
        // TODO: Event polling should be done inside the states
        sf::Event event{};
        while (window_.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window_.close();
        }

        current_state_->draw_window();

    }
}

void Gui::change_game_state(WindowState* new_state) {
    delete current_state_;
    current_state_ = new_state;
}
