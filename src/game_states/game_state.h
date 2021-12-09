#ifndef TOWER_DEFENSE_12_GAME_STATE_H
#define TOWER_DEFENSE_12_GAME_STATE_H

#include "window_state.h"
#include <iostream>
#include "../Game.hpp"
#include "../tower.hpp"
#include "../gui_elements/TowerButton.h"
#include "../gui_elements/EnemyGui.h"
#include "../utils/json_driver.h"


enum GameButtonTarget {QuitToMenu, SaveGame, StartWave, SellTower, UpgradeTower};

// enum TowerTypes {GunnerType, BomberType, Attack3, Attack4, ClockerType, SeerType, StereoType, Support4};

class GameState: public WindowState {
public:
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

    void draw_info();

    void draw_current_state() override;

    void saveGame();

    void quitToMenu();

    void startWave();

    void buyTower(Tower*);

    void sellTower(Tower*);

private:
    std::map<GameButtonTarget, Button*> buttons_;
    std::map<TowerTypes, TowerButton*> towerButtons_;
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
