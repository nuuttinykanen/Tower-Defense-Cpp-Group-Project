#include <SFML/Graphics.hpp>

#ifndef TOWER_DEFENSE_12_GUI_H
#define TOWER_DEFENSE_12_GUI_H

#endif //TOWER_DEFENSE_12_GUI_H

class Gui {
public:
    Gui(int width, int height);

    void start_main_window() const;

    int get_screen_width() const { return screen_width_;}
    int get_screen_height() const { return screen_height_;}

private:
    int screen_width_;
    int screen_height_;
};