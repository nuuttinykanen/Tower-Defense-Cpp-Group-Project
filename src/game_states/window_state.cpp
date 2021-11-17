#include "window_state.h"


WindowState::WindowState(sf::RenderWindow& window)
    : window_(window){

}

void WindowState::draw_window() {
    window_.clear();

    advance_state();
    draw_current_state();

    window_.display();
}
