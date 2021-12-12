#ifndef TOWER_DEFENSE_12_GAME_STATE_H
#define TOWER_DEFENSE_12_GAME_STATE_H

#include "window_state.h"
#include <iostream>
#include "../Game.hpp"
#include "../towers/tower.hpp"
#include "../gui_elements/TowerButton.h"
#include "../utils/json_driver.h"
#include "finish_state.h"

enum GameButtonTarget {QuitToMenuTarget, SaveGameTarget, StartWaveTarget, SellTowerTarget, UpgradeTowerTarget, DeselectTowerTarget};

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
    GameState(sf::RenderWindow& window, Gui* gui, int level_number);
    ~GameState();

    void GenerateButtons();

    void GenerateEnemies();

    void GenerateTowers();

    void GenerateProjectiles();

    void GenerateProjectileHitSprites();

    void AdvanceState() override;

    void PollEvents() override;

    void DrawTowerRange(int tx, int ty, Tower* tow);

    void DrawPlayerInfo();

    void DrawTowerInfo(Tower* tow);

    void DrawPopupText();

    void DrawCurrentState() override;

    void SaveGame();

    void QuitToMenu();

    void StartWave();

    void BuyTower(Tower* tower);

    void SellTower();

    void UpgradeTower();

private:
    std::map<GameButtonTarget, Button*> buttons_;
    std::map<TowerTypes, TowerButton*> tower_buttons_;
    std::map<std::string, sf::Sprite> enemy_sprites_;
    std::map<std::string, sf::Sprite> tower_sprites_;
    std::map<std::string, sf::Sprite> projectile_sprites_;
    std::map<std::string, sf::Sprite> projectile_hit_sprites_;
    Game* game_;
    LevelMap* level_map_;
    int level_number_;
    Player* player_;

    bool over_upgrade = false;
    bool is_tower_selected = false;
    SelectedTower upgrade_preview_ = {};
    SelectedTower selected_tower_ = {};
    PopupText popup_text_ ={1, nullptr, false};

    void AddPopup(const string& content, int posX, bool permanent);

    void RemovePopup();
};

// TODO: Add the rest of the towers here as well
static Tower* GetTowerByType(TowerTypes type) {
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
        case CursedKidType:
            return new CursedKid();
        case MaskedKidType:
            return new MaskedKid();
        case MaskedGodType:
            return new MaskedGod();
        case KnifeBotType:
            return new KnifeBot();
        case KnifeBot2Type:
            return new KnifeBot2();
        case SwordBotType:
            return new SwordBot();
        case ClockerType:
            return new Clocker();
        case ClockerBlockerType:
            return new ClockBlocker();
        case SeerType:
            return new Seer();
        case MotherBrainType:
            return new MotherBrain();
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
