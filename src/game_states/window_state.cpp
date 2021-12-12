#include "window_state.h"
#include "../gui.h"


WindowState::WindowState(sf::RenderWindow& window, Gui* gui)
    : window_(window), gui_(gui) {

}

void WindowState::DrawWindow() {
    window_.clear(Color(38, 38, 38));

    AdvanceState();
    DrawCurrentState();

    window_.display();
}

sf::Font& WindowState::GetFont() {
    return gui_->GetGlobalObjects()->getFont();
}