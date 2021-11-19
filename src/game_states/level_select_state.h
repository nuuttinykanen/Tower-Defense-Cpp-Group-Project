#ifndef TOWER_DEFENSE_12_LEVEL_SELECT_STATE_H
#define TOWER_DEFENSE_12_LEVEL_SELECT_STATE_H

#include "window_state.h"
#include <iostream>
// #include "../Gui.h"


class LevelSelectState: public WindowState {
public:
    LevelSelectState(sf::RenderWindow& window, Gui* gui);
    ~LevelSelectState() override = default;

    void advance_state() override;

    void draw_current_state() override;
private:
};




#endif //TOWER_DEFENSE_12_LEVEL_SELECT_STATE_H
