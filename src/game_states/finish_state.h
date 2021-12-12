#ifndef TOWER_DEFENSE_12_FINISH_STATE_H
#define TOWER_DEFENSE_12_FINISH_STATE_H

#include "window_state.h"
#include <iostream>
#include "../Gui.h"
enum FinishButtonTarget {PlayAgain, MainMenu};


class FinishState: public WindowState {
public:
    FinishState(sf::RenderWindow& window, Gui* gui, int level_number);
    ~FinishState() override;

    void AdvanceState() override;
    void PollEvents() override;
    void DrawCurrentState() override;



private:
    std::map<FinishButtonTarget, Button*> buttons_;
    void generate_buttons();
    sf::Text text_;
    int level_number_;
};




#endif //TOWER_DEFENSE_12_FINISH_STATE_H
