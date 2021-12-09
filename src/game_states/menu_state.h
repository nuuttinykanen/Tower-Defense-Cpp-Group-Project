#ifndef TOWER_DEFENSE_12_MENU_STATE_H
#define TOWER_DEFENSE_12_MENU_STATE_H
#include "window_state.h"
#include "SFML/Graphics.hpp"
#include <iostream>

enum MenuButtonTarget {StartLatestSave, StartLevelSelect, Quit};


class MenuState: public WindowState {
public:
    MenuState(sf::RenderWindow& window, Gui* gui);

    ~MenuState();

    void advance_state() override;

    void draw_current_state() override;

    void poll_events() override;

    void start_latest_save();

    void startLevelSelect();

    void quit();

private:
    int count_ = 0;
    std::map<MenuButtonTarget, Button*> buttons_;

};
#endif //TOWER_DEFENSE_12_MENU_STATE_H
