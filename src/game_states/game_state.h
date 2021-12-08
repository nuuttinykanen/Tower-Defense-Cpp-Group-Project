#ifndef TOWER_DEFENSE_12_GAME_STATE_H
#define TOWER_DEFENSE_12_GAME_STATE_H

#include "window_state.h"
#include <iostream>
#include "../Game.hpp"
#include "../tower.hpp"
#include "../gui_elements/TowerButton.h"
#include "../gui_elements/EnemyGui.h"
#include "../utils/json_driver.h"

enum GameButtonTarget {QuitToMenu, StartWave, SellTower, UpgradeTower};

enum TowerSelectionTarget {Attack1, Attack2, Attack3, Attack4, Support1, Support2, Support3, Support4};

class GameState: public WindowState {
public:
    // TODO: Specify which level to start
    GameState(sf::RenderWindow& window, Gui* gui, int levelNumber);
    ~GameState();

    void generateButtons();

    void generateEnemies();

    void generateTowers();

    void generateProjectiles();

    void generateProjectileHitSprites();

    void advance_state() override;

    void poll_events() override;

    void draw_tower_range(LevelMap* map, TowerSquare* tsq);

    void draw_current_state() override;

    void quitToMenu();

    void startWave();

    void buyTower(Tower*);

private:
    std::map<GameButtonTarget, Button*> buttons_;
    std::map<TowerSelectionTarget, TowerButton*> towerButtons_;
    std::map<std::string, sf::Sprite> enemySprites_;
    std::map<std::string, sf::Sprite> towerSprites_;
    std::map<std::string, sf::Sprite> projectileSprites_;
    std::map<std::string, sf::Sprite> projectileHitSprites_;
    Game* game_;
    LevelMap* levelMap_;
    int levelNumber_;
    Player* player_;
};
#endif //TOWER_DEFENSE_12_GAME_STATE_H
