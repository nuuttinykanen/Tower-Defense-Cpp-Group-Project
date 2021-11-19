#include "window_state.h"
#include "../Gui.h"


WindowState::WindowState(sf::RenderWindow& window, Gui* gui)
    : window_(window), gui_(gui) {

}

void WindowState::draw_window() {
    window_.clear();

    advance_state();
    draw_current_state();

    window_.display();
}
