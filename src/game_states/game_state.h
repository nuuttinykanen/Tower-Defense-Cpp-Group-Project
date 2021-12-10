#ifndef TOWER_DEFENSE_12_GAME_STATE_H
#define TOWER_DEFENSE_12_GAME_STATE_H

#include "window_state.h"
#include <iostream>
#include "../Game.hpp"
#include "../tower.hpp"
#include "../gui_elements/TowerButton.h"
#include "../gui_elements/EnemyGui.h"
#include "../utils/json_driver.h"


enum GameButtonTarget {QuitToMenu, SaveGame, StartWave, SellTower, UpgradeTower, DeselectTower};

struct SelectedTower {
    int x;
    int y;
    TowerSquare* tower;
    bool canUpgrade;
};

struct PopupText {
    float opacity;
    sf::Text* text;
    // Doesn't fade away
    bool permanent;
};
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

    void draw_tower_range(TowerSquare* tsq);

    void draw_player_info();

    void draw_selected_tower_info();

    void draw_popup_text();

    void draw_current_state() override;

    void saveGame();

    void quitToMenu();

    void startWave();

    void buyTower(Tower*);

    void sellTower();

    void upgradeTower();

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

    bool isTowerSelected = false;
    SelectedTower selectedTower_ = {};
    PopupText popupText_ ={1, nullptr, false};

    void add_buying_popup();

    void add_not_enough_money_popup();

    void add_popup(const string& content, int posX, bool permanent);

    void remove_popup();
};

// TODO: Add the rest of the towers here as well
static Tower* getTowerByType(TowerTypes type) {
    switch (type) {
        case GunnerType:
            return new Gunner();
        case MultiGunnerType:
            return new Multigunner();
        case GunFiendType:
            return new GunFiend();
        case BomberType:
            return new Bomber();
        case SuperBomberType:
            return new SuperBomber();
        case UltraBomberType:
            return new UltraBomber();
        case Attack3:
            return new Gunner();
        case Attack4:
            return new Gunner();
        case ClockerType:
            return new Clocker();
        case ClockerBlockerType:
            return new ClockBlocker();
        case SeerType:
            return new Seer();
        case MotherBrainType:
            return new Gunner();
        case StereoType:
            return new StereoDude();
        case DJDudeType:
            return new DJDude();
        case Support4:
            return new Seer();
        default:
            throw std::invalid_argument("Invalid tower type");
    }
}

#endif //TOWER_DEFENSE_12_GAME_STATE_H
