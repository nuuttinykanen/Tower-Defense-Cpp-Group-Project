#ifndef TOWER_DEFENSE_12_GAME_STATE_H
#define TOWER_DEFENSE_12_GAME_STATE_H

#include "window_state.h"
#include <iostream>

class GameState: public WindowState {
public:
    // TODO: Specify which level to start
    GameState(sf::RenderWindow& window, Gui* gui);
    ~GameState() override = default;

    void advance_state() override;

    void draw_current_state() override;
private:
};
#endif //TOWER_DEFENSE_12_GAME_STATE_H
