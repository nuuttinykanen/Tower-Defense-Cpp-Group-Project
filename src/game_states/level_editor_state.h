#ifndef TOWER_DEFENSE_12_LEVEL_EDITOR_STATE_H
#define TOWER_DEFENSE_12_LEVEL_EDITOR_STATE_H

#include "window_state.h"
#include <iostream>
// #include "../Gui.h"

class LevelEditorState: public WindowState {
public:
    LevelEditorState(sf::RenderWindow& window, Gui* gui);
    ~LevelEditorState() override = default;

    void advance_state() override;

    void draw_current_state() override;
private:
};




#endif //TOWER_DEFENSE_12_LEVEL_EDITOR_STATE_H
