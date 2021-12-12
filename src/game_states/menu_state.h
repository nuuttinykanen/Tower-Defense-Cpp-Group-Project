#ifndef TOWER_DEFENSE_12_MENU_STATE_H
#define TOWER_DEFENSE_12_MENU_STATE_H
#include "window_state.h"
#include "SFML/Graphics.hpp"
#include <iostream>

enum MenuButtonTarget {StartLatestSaveTarget, StartLevelSelectTarget, QuitTarget};


class MenuState: public WindowState {
public:
    MenuState(sf::RenderWindow& window, Gui* gui);

    ~MenuState();

    void AdvanceState() override;

    void DrawCurrentState() override;

    void PollEvents() override;

    void StartLatestSave();

    void StartLevelSelect();

    void Quit();

private:
    int count_ = 0;
    std::map<MenuButtonTarget, Button*> buttons_;

};
#endif //TOWER_DEFENSE_12_MENU_STATE_H
