#ifndef TOWER_DEFENSE_12_WINDOW_STATE_H
#define TOWER_DEFENSE_12_WINDOW_STATE_H

#include <SFML/Graphics.hpp>


// Base class for all game states

class WindowState {
public:
    WindowState(sf::RenderWindow& window);
    virtual ~WindowState() = 0;
    void draw_window();

    // Advance the current game state
    virtual void advance_state() = 0;

    // Draw the current state after advancing
    virtual void draw_current_state() = 0;

    // Protected allows us to access this from child classes
protected:
    sf::RenderWindow& window_;
};

#endif //TOWER_DEFENSE_12_WINDOW_STATE_H
