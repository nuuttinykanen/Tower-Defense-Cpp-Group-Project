#ifndef TOWER_DEFENSE_12_FINISHSTATE_H
#define TOWER_DEFENSE_12_FINISHSTATE_H

#include "window_state.h"
#include <iostream>
#include "../Gui.h"
enum FinishButtonTarget {PlayAgain, MainMenu};


class FinishState: public WindowState {
public:
    FinishState(sf::RenderWindow& window, Gui* gui, int levelNumber);
    ~FinishState() override;

    void advance_state() override;
    void poll_events() override;
    void draw_current_state() override;



private:
    std::map<FinishButtonTarget, Button*> buttons_;
    void generate_buttons();
    sf::Text text_;
    int levelNumber_;
};




#endif //TOWER_DEFENSE_12_FINISHSTATE_H
