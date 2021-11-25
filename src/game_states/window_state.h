#ifndef TOWER_DEFENSE_12_WINDOW_STATE_H
#define TOWER_DEFENSE_12_WINDOW_STATE_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "../gui_elements/Button.h"

// Forward declare gui as an incomplete type
class Gui;

// Base class for all game states

class WindowState {
public:
    WindowState(sf::RenderWindow& window, Gui* gui);
    virtual ~WindowState() = default;;
    void draw_window();

    // Advance the current game state
    virtual void advance_state() = 0;

    // Draw the current state after advancing
    virtual void draw_current_state() = 0;

    // Goes through all the sfml events (clicking, button presses etc.)
    virtual void poll_events() = 0;

    sf::Font& getFont();
    // Protected allows us to access this from child classes
protected:
    sf::RenderWindow& window_;
    Gui* gui_;

    // Button handling, button and its function

};


#endif //TOWER_DEFENSE_12_WINDOW_STATE_H
