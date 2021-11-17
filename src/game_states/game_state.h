#ifndef TOWER_DEFENSE_12_GAME_STATE_H
#define TOWER_DEFENSE_12_GAME_STATE_H

#include "window_state.h"
#include <iostream>

class GameState: public WindowState {
public:
    GameState(sf::RenderWindow& window);
    ~GameState() override = default;

    void advance_state() override;

    void draw_current_state() override;
private:
};
#endif //TOWER_DEFENSE_12_GAME_STATE_H
