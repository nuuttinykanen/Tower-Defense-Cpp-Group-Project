#ifndef TOWER_DEFENSE_12_LEVEL_EDITOR_STATE_H
#define TOWER_DEFENSE_12_LEVEL_EDITOR_STATE_H

#include "window_state.h"
#include <iostream>

class LevelEditorState: public WindowState {
public:
    LevelEditorState(sf::RenderWindow& window);
    ~LevelEditorState() override = default;

    void advance_state() override;

    void draw_current_state() override;
private:
};




#endif //TOWER_DEFENSE_12_LEVEL_EDITOR_STATE_H
