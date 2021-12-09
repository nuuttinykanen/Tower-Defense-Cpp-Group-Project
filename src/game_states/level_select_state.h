#ifndef TOWER_DEFENSE_12_LEVEL_SELECT_STATE_H
#define TOWER_DEFENSE_12_LEVEL_SELECT_STATE_H

#include "window_state.h"
#include <iostream>
#include "../utils/json_driver.h"
#include "game_state.h"
#include "menu_state.h"
#include "../Gui.h"
// #include "../Gui.h"

class LevelSelectState: public WindowState {
public:
    LevelSelectState(sf::RenderWindow& window, Gui* gui);
    ~LevelSelectState() override = default;

    void advance_state() override;

    void poll_events() override;

    void draw_current_state() override;

    void generateButtons();
private:
    std::map<int, Button*> buttons_;

};




#endif //TOWER_DEFENSE_12_LEVEL_SELECT_STATE_H
