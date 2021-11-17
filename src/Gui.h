#ifndef TOWER_DEFENSE_12_GUI_H
#define TOWER_DEFENSE_12_GUI_H

#include <SFML/Graphics.hpp>
#include "game_states/window_state.h"
#include "game_states/menu_state.h"


class Gui {
public:
    Gui(int width, int height);

    void start_main_loop();

    void change_game_state(WindowState* new_state);

    int get_screen_width() const { return screen_width_;}
    int get_screen_height() const { return screen_height_;}

private:
    sf::RenderWindow window_;
    WindowState* current_state_;
    int screen_width_;
    int screen_height_;
};

#endif //TOWER_DEFENSE_12_GUI_H