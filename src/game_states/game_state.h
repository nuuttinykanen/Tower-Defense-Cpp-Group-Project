#ifndef TOWER_DEFENSE_12_GAME_STATE_H
#define TOWER_DEFENSE_12_GAME_STATE_H

#include "window_state.h"
#include <iostream>
#include "../Game.hpp"
enum GameButtonTarget {QuitToMenu, StartWave, SellTower, UpgradeTower};

class GameState: public WindowState {
public:
    // TODO: Specify which level to start
    GameState(sf::RenderWindow& window, Gui* gui);
    ~GameState();

    void advance_state() override;

    void poll_events() override;

    void draw_current_state() override;

    void quitToMenu();

    void startWave();
private:
    std::map<GameButtonTarget, Button*> buttons_;
    Game* game_;
    LevelMap* levelMap_;

};
#endif //TOWER_DEFENSE_12_GAME_STATE_H
