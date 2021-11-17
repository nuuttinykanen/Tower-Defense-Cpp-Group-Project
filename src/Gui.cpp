
#include "Gui.h"

Gui::Gui(int width, int height)
    : screen_width_(width), screen_height_(height),
      current_state_(new MenuState(window_)),
    window_(sf::RenderWindow(sf::VideoMode(width, height), "Hello world!"))
    {
    window_.setFramerateLimit(60);
    start_main_loop();
}

void Gui::start_main_loop() {

    while (window_.isOpen())
    {
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
