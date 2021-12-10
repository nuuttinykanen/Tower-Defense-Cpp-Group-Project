#include "../Gui.h"
#include "game_state.h"
#include "menu_state.h"
#include <cmath>

#define TOWER_BUTTON_GRID_START_X 1065
#define TOWER_BUTTON_GRID_START_Y 15
#define TOWER_BUTTON_OFFSET 110



GameState::GameState(sf::RenderWindow &window, Gui* gui, int levelNumber): WindowState(window, gui) {

    generateButtons();
    generateEnemies();
    generateTowers();
    generateProjectiles();
    generateProjectileHitSprites();

    // 0 level number means that we are loading the latest save, also check that the file exists
    if (levelNumber == 0 && JSON::latestSaveExists()) {
        game_ = JSON::loadLatestSave();
        levelMap_ = &game_->GetMap();
        levelNumber_ = levelMap_->getLevelNumber();
        player_ = &game_->GetPlayer();

    } else {
        if (!JSON::latestSaveExists() && levelNumber == 0) { levelNumber_ = 1;}
        else { levelNumber_ = levelNumber;}

        levelMap_ = JSON::loadLevelMap(levelNumber_);
        auto waves = JSON::loadWaves(levelNumber_);
        std::cout << waves.size() << std::endl;
        player_ = new Player(100);
        game_ = new Game( *levelMap_, *player_, waves);
    }
}
GameState::~GameState() {
    for (auto b : buttons_) {
        delete b.second;
    }
    for (auto t : towerButtons_) {
        delete t.second;
    }
}

void GameState::advance_state() {
    game_->UpdateState();

}

void GameState::draw_tower_range(int tx, int ty, Tower* tow) {
    if(tow == nullptr) return;

    for(auto it : levelMap_->GetSquares()) {
        double x = it.first.first;
        double y = it.first.second;
        if(sqrt(pow(tx - x, 2.0) + pow(ty - y, 2.0)) <= tow->GetRange()) {
            sf::RectangleShape rectangle(sf::Vector2f(1, 1));
            rectangle.setSize(sf::Vector2f(35, 35));
            rectangle.setPosition(x * 35, y * 35);
            rectangle.setOutlineThickness(1);
            rectangle.setOutlineColor(sf::Color::Black);
            sf::Color color = sf::Color::White;
            color.a = 90;
            rectangle.setFillColor(color);
            window_.draw(rectangle);
        }
    }
}

bool buyingTower = false;
Tower* newTower = nullptr;

void GameState::draw_current_state() {
    for (auto b : buttons_) {
        switch (b.first) {
            case UpgradeTower:
                if (!isTowerSelected || !selectedTower_.canUpgrade) continue;
                break;
            case SellTower:
                if (!isTowerSelected) continue;
                break;
            case DeselectTower:
                if (!isTowerSelected) continue;
                break;
            default:
                break;
        }
        b.second->draw(window_);
    }
    for (auto t : towerButtons_)  {
        t.second->draw(window_, player_->GetMoney());
    }
    auto globals = gui_->getGlobalObjects();

    LevelMap& map = game_->GetMap();

    // Draw enemies and path
    for(auto it : map.GetEnemySquares()) {
        auto freeSprite = globals->getEnemySquareSprite();
        freeSprite.setScale(2,2);
        freeSprite.setPosition(it.second->GetX()*35, it.second->GetY()*35);
        window_.draw(freeSprite);
    }

    // Draw free squares
    for(auto it : map.GetFreeSquares()) {
        auto freeSprite = globals->getFreeSquareSprite();
        freeSprite.setScale(2, 2);
        freeSprite.setPosition(it.second->GetX() * 35, it.second->GetY() * 35);
        window_.draw(freeSprite);
    }

    draw_player_info();

    // Draw towers
    for(auto it : map.GetTowerSquares()) {

        auto freeSprite = globals->getFreeSquareSprite();
        freeSprite.setScale(2, 2);
        freeSprite.setPosition(it.second->GetX()*35, it.second->GetY()*35);
        window_.draw(freeSprite);


        sf::Sprite tow_sprite = towerSprites_.at(it.second->GetTower()->GetName());
        tow_sprite.setScale(1.9,1.9);
        tow_sprite.setPosition(it.second->GetX() * 35, it.second->GetY() * 35);

        draw_selected_tower_info();
        window_.draw(tow_sprite);
        // Draw cooldown bar
        auto tow = (AttackTower*)it.second->GetTower();
        if(game_->isWaveInProgress() && it.second->GetTower()->GetMainType() == "attack" && tow->CurrentCooldown() > 0) {
            sf::RectangleShape bar(sf::Vector2f(20.0 * (double)((double)tow->CurrentCooldown() / (double)tow->GetCooldownLimit()), 4));
            bar.setSize(sf::Vector2f(18.0 * (double)((double)tow->CurrentCooldown() / (double)tow->GetCooldownLimit()), 2));
            bar.setFillColor(sf::Color::White);
            bar.setOutlineThickness(1);
            bar.setOutlineColor(sf::Color::Black);
            bar.setScale(2, 2);
            bar.setPosition(it.second->GetX() * 35 + 1, it.second->GetY() * 35 + 31);

            window_.draw(bar);
        }
    }
    for(auto it : map.GetEnemySquares()) {
        if(it.second->ContainsEnemies()) {
            for(Enemy* en : it.second->GetEnemies()) {
                sf::Sprite en_sprite = enemySprites_.at(en->GetName());
                en_sprite.setScale(2, 2);
                en_sprite.setPosition(it.second->GetX()*35, it.second->GetY()*35);
                window_.draw(en_sprite);


                // Draw health bar
                sf::RectangleShape bar(sf::Vector2f(20.0 * (double)((double)en->GetHealth() / (double)en->GetMaxHealth()), 4));
                bar.setSize(sf::Vector2f(20.0 * (double)((double)en->GetHealth() / (double)en->GetMaxHealth()), 2));
                bar.setFillColor(sf::Color::Magenta);
                bar.setScale(2, 2);
                bar.setPosition(it.second->GetX()*35, it.second->GetY()*35 + 31);
                window_.draw(bar);
            }
        }
    }

    // Draw enemy death sprites
    for(auto it : map.GetProjectileMarks()) {
        if(!game_->isWaveInProgress()) break;
        for(auto coords : it.second) {
            auto sprite = this->projectileHitSprites_[it.first];
            sprite.setScale(2, 2);
            sprite.setPosition(coords.first * 35, coords.second * 35);
            window_.draw(sprite);
        }
    }

    // Draw projectiles
    for(auto it : map.GetProjectiles()) {
        if(it->GetLocation() != nullptr && it->GetSender() != nullptr) {
            auto projSprite = projectileSprites_.at(it->GetSender()->GetName());
            projSprite.setScale(0.2,0.2);
            projSprite.setPosition(it->GetLocation()->GetX() * 35.5, it->GetLocation()->GetY()* 35.5);
            window_.draw(projSprite);
        }
    }

    if (newTower != nullptr && buyingTower) {
        auto mouse_pos = window_.mapPixelToCoords(sf::Mouse::getPosition(window_));
        for (auto area: map.GetSquares()) {
            auto freeSprite = this->towerSprites_.at(newTower->GetName());
            freeSprite.setScale(2, 2);
            freeSprite.setPosition(area.second->GetX() * 35, area.second->GetY() * 35);
            if (freeSprite.getGlobalBounds().contains(mouse_pos)) {
                draw_tower_range(area.second->GetX(), area.second->GetY(), newTower);
                window_.draw(freeSprite);
                break;
            }
        }
    }

    draw_popup_text();

}


void GameState::poll_events() {
    sf::Event event{};
    LevelMap& map = game_->GetMap();
    auto globals = gui_->getGlobalObjects();
    while (window_.pollEvent(event))
    {
        if (event.type == sf::Event::Closed) {
            saveGame();
            window_.close();
        }


        //buys and adds a chosen tower to a clicked free square
        if (buyingTower && event.type == sf::Event::MouseButtonReleased) {
            auto placeTo = window_.mapPixelToCoords(sf::Mouse::getPosition(window_));
            for(auto area : map.GetFreeSquares()) {
                auto freeSprite = globals->getFreeSquareSprite();
                freeSprite.setScale(2, 2);
                freeSprite.setPosition(area.second->GetX() * 35, area.second->GetY() * 35);
                if(freeSprite.getGlobalBounds().contains(placeTo)) {
                    this->levelMap_->PlaceTower(area.second->GetX(), area.second->GetY(), newTower);
                    buyingTower = false;
                    remove_popup();
                    buyTower(newTower);
                    break;
                }
            }
        }
        // 0 -> primary click, 1-> secondary
        if (event.type == sf::Event::MouseButtonReleased) {
            if (event.mouseButton.button == 0) {
                auto mouse_pos = window_.mapPixelToCoords(sf::Mouse::getPosition(window_));

                for (auto b : buttons_) {
                    // Move to next one if this button is not clicked
                    if (!b.second->contains(mouse_pos)) continue;
                    switch (b.first) {

                        case QuitToMenu:
                            quitToMenu();
                            return;
                        case SaveGame:
                            saveGame();
                            add_popup("Game saved!", 400, false);
                            return;
                        case StartWave:
                            buyingTower = false;
                            remove_popup();
                            startWave();
                            return;
                        case SellTower:
                            buyingTower = false;
                            remove_popup();
                            sellTower();
                            return;
                        case UpgradeTower:
                            buyingTower = false;
                            remove_popup();
                            upgradeTower();
                            return;
                        case DeselectTower:
                            isTowerSelected = false;
                            return;
                    }
                }

                for (auto t : towerButtons_) {
                    if (!t.second->contains(mouse_pos)) continue;

                    newTower = getTowerByType(t.first);

                    if(newTower->GetPrice() <= player_->GetMoney()) {
                        add_popup("Place the " + newTower->GetName() + " in a free square!", 185, true);
                        buyingTower = true;
                    } else {
                        add_popup("You don't have enough money!", 200, false);
                        delete newTower;
                    }

                }
                for(auto area : map.GetTowerSquares()) {
                    auto freeSprite = globals->getFreeSquareSprite();
                    freeSprite.setScale(2, 2);
                    freeSprite.setPosition(area.second->GetX() * 35, area.second->GetY() * 35);
                    if(freeSprite.getGlobalBounds().contains(mouse_pos)) {
                        if (selectedTower_.tower == area.second) {
                            isTowerSelected = false;
                            selectedTower_.tower = nullptr;
                            break;
                        }
                        isTowerSelected = true;
                        selectedTower_.tower = area.second;
                        selectedTower_.canUpgrade = area.second->GetTower()->CanUpgrade();
                        selectedTower_.x = area.second->GetX();
                        selectedTower_.y = area.second->GetY();
                        break;
                    }
                }

            } else if (event.mouseButton.button == 1) {
                //right click does nothing
            }

        }
    }
    if (game_->isGameOver()) {
        auto newState = new FinishState(window_, gui_, levelNumber_);

        gui_->change_game_state(newState);
        return;
    }
}

void GameState::quitToMenu() {
    saveGame();
    gui_->change_game_state(new MenuState(window_, gui_));
}

void GameState::startWave() {
    if (game_->isWaveInProgress()) {
        add_popup("Can't start a new wave yet!", 200, false);
        return;
    }
    isTowerSelected = false;
    game_->StartWave();
    add_popup("Starting wave " + std::to_string(game_->GetWaveNumber()), 350, false);

}

void GameState::buyTower(Tower* tower) {
    player_->AddTower(tower);
}

void GameState::sellTower() {
    isTowerSelected = false;
    auto tower = selectedTower_.tower->GetTower();
    game_->SellTower(selectedTower_.tower);
    this->levelMap_->EraseTowerAt(selectedTower_.tower);

    player_->SellTower(tower);

}

void GameState::upgradeTower() {

    if (selectedTower_.tower != nullptr) {
        auto upgrade = selectedTower_.tower->GetTower()->Upgrade();
        if(upgrade != nullptr) {
            if(upgrade->GetPrice() > player_->GetMoney()) {
                add_popup("You don't have enough money!", 200, false);
            } else {
                player_->AddTower(upgrade);
                int x = selectedTower_.tower->GetX();
                int y = selectedTower_.tower->GetY();
                this->levelMap_->EraseTowerAt(selectedTower_.tower);
                this->levelMap_->PlaceTower(x, y, upgrade);
            }
        } else {
            add_popup("No upgrade available!", 200, false);
        }
    }
    isTowerSelected = false;

}

void GameState::generateButtons() {
    // Generate buttons

    auto startWaveButton = new Button(sf::Vector2f(215, 40), sf::Vector2f(1060, 550),
                                      "Start wave!", this->getFont(), 20, 2, 8);
    buttons_[GameButtonTarget::StartWave] = startWaveButton;

    auto saveButton = new Button(sf::Vector2f(215, 40), sf::Vector2f(1060, 610),
                                      "Save game", this->getFont(), 20, 20, 8);
    buttons_[GameButtonTarget::SaveGame] = saveButton;

    auto quitButton = new Button(sf::Vector2f (215, 40), sf::Vector2f(1060, 670),
                                  "Quit game",this->getFont(), 20, 18, 8);
    buttons_[GameButtonTarget::QuitToMenu] = quitButton;

    auto upgradeTowerButton = new Button(sf::Vector2f(300, 40), sf::Vector2f(700
                                                 , 550),
                                         "Upgrade tower", this->getFont(), 20, 18, 8);
    buttons_[GameButtonTarget::UpgradeTower] = upgradeTowerButton;

    auto sellTowerButton = new Button(sf::Vector2f(300, 40), sf::Vector2f(700, 610),
                                      "Sell tower", this->getFont(), 20, 50, 8);
    buttons_[GameButtonTarget::SellTower] = sellTowerButton;
    auto deselectTowerButton = new Button(sf::Vector2f(300, 40), sf::Vector2f(700, 670),
                                      "Deselect tower", this->getFont(), 20, 18, 8);
    buttons_[GameButtonTarget::DeselectTower] = deselectTowerButton;


    // TODO: Add the correct sprites here when they are made
    // TODO: Add correct costs in the end
    auto attack1Button = new TowerButton(sf::Vector2f(TOWER_BUTTON_GRID_START_X, TOWER_BUTTON_GRID_START_Y), gui_->getGlobalObjects()->getGunnerSprite(),
                                         getFont(), 50);
    towerButtons_[TowerTypes::GunnerType] = attack1Button;

    auto attack2Button = new TowerButton(sf::Vector2f(TOWER_BUTTON_GRID_START_X + TOWER_BUTTON_OFFSET, TOWER_BUTTON_GRID_START_Y), gui_->getGlobalObjects()->getBomberSprite(),
                                         getFont(), 100);
    towerButtons_[TowerTypes::BomberType] = attack2Button;

    auto attack3Button = new TowerButton(sf::Vector2f(TOWER_BUTTON_GRID_START_X, TOWER_BUTTON_GRID_START_Y + TOWER_BUTTON_OFFSET), gui_->getGlobalObjects()->getGunnerSprite(),
                                         getFont(), 200);
    towerButtons_[TowerTypes::Attack3] = attack3Button;

    auto attack4Button = new TowerButton(sf::Vector2f(TOWER_BUTTON_GRID_START_X + TOWER_BUTTON_OFFSET, TOWER_BUTTON_GRID_START_Y + TOWER_BUTTON_OFFSET), gui_->getGlobalObjects()->getGunnerSprite(),
                                         getFont(), 300);
    towerButtons_[TowerTypes::Attack4] = attack4Button;

    auto support1Button = new TowerButton(sf::Vector2f(TOWER_BUTTON_GRID_START_X, TOWER_BUTTON_GRID_START_Y + 2 * TOWER_BUTTON_OFFSET), gui_->getGlobalObjects()->getClockerSprite(),
                                          getFont(), 50);
    towerButtons_[TowerTypes::ClockerType] = support1Button;

    auto support2Button = new TowerButton(sf::Vector2f(TOWER_BUTTON_GRID_START_X + TOWER_BUTTON_OFFSET, TOWER_BUTTON_GRID_START_Y + 2 * TOWER_BUTTON_OFFSET), gui_->getGlobalObjects()->getSeerSprite(),
                                          getFont(), 50);
    towerButtons_[TowerTypes::SeerType] = support2Button;

    auto support3Button = new TowerButton(sf::Vector2f(TOWER_BUTTON_GRID_START_X, TOWER_BUTTON_GRID_START_Y + 3 * TOWER_BUTTON_OFFSET), gui_->getGlobalObjects()->getStereoDudeSprite(),
                                          getFont(), 50);
    towerButtons_[TowerTypes::StereoType] = support3Button;

    auto support4Button = new TowerButton(sf::Vector2f(TOWER_BUTTON_GRID_START_X + TOWER_BUTTON_OFFSET, TOWER_BUTTON_GRID_START_Y + 3*TOWER_BUTTON_OFFSET), gui_->getGlobalObjects()->getGunnerSprite(),
                                          getFont(), 50);
    towerButtons_[TowerTypes::Support4] = support4Button;
}

void GameState::generateEnemies() {
    enemySprites_["Zombie"] = gui_->getGlobalObjects()->getZombieSprite();
    enemySprites_["Michael Myers"] = gui_->getGlobalObjects()->getMichaelSprite();
    enemySprites_["Zombie Horde"] = gui_->getGlobalObjects()->getHordeSprite();
    enemySprites_["Dracula"] = gui_->getGlobalObjects()->getDraculaSprite();
    enemySprites_["Bat"] = gui_->getGlobalObjects()->getBatSprite();
}

void GameState::generateTowers() {
    towerSprites_["Bomber"] = gui_->getGlobalObjects()->getBomberSprite();
    towerSprites_["Gunner"] = gui_->getGlobalObjects()->getGunnerSprite();
    towerSprites_["Super Bomber"] = gui_->getGlobalObjects()->getSuperBomberSprite();
    towerSprites_["Ultra Bomber"]  = gui_->getGlobalObjects()->getUltraBomberSprite();
    towerSprites_["Stereo Dude"]  = gui_->getGlobalObjects()->getStereoDudeSprite();
    towerSprites_["DJ Dude"]  = gui_->getGlobalObjects()->getDJDudeSprite();
    towerSprites_["Seer"]  = gui_->getGlobalObjects()->getSeerSprite();
    towerSprites_["Mother Brain"]  = gui_->getGlobalObjects()->getMotherBrainSprite();
    towerSprites_["Clocker"]  = gui_->getGlobalObjects()->getClockerSprite();
    towerSprites_["Clock Blocker"]  = gui_->getGlobalObjects()->getClockBlockerSprite();
    towerSprites_["Multigunner"]  = gui_->getGlobalObjects()->getMultigunnerSprite();
    towerSprites_["Gun Fiend"]  = gui_->getGlobalObjects()->getGunFiendSprite();
}

void GameState::generateProjectiles() {
    projectileSprites_["Bomber"] = gui_->getGlobalObjects()->getBomberSprite();
    projectileSprites_["Gunner"] = gui_->getGlobalObjects()->getGunnerSprite();
    projectileSprites_["Super Bomber"] = gui_->getGlobalObjects()->getSuperBomberSprite();
    projectileSprites_["Ultra Bomber"]  = gui_->getGlobalObjects()->getUltraBomberSprite();
    projectileSprites_["Multigunner"]  = gui_->getGlobalObjects()->getMultigunnerSprite();
    projectileSprites_["Gun Fiend"]  = gui_->getGlobalObjects()->getGunFiendSprite();
}

void GameState::generateProjectileHitSprites() {
    projectileHitSprites_["bomb"] = gui_->getGlobalObjects()->getBombProjecHit1Sprite();
    projectileHitSprites_["bullet"] = gui_->getGlobalObjects()->getBombProjecHit2Sprite();
}

void GameState::saveGame() {
    JSON::saveCurrentGame(game_, levelNumber_);
}

void GameState::draw_player_info() {
    sf::Text pHealth;
    sf::Text pMoney;
    sf::Text waves;

    pHealth.setFont(this->getFont());
    pMoney.setFont(this->getFont());
    waves.setFont(this->getFont());

    std::string health = "Health: " + std::to_string(this->player_->GetHealth());
    std::string money = "Money: " + std::to_string(int(this->player_->GetMoney()));
    std::string waveText = "Wave " + std::to_string(game_->GetWaveNumber()) + " / " + std::to_string(game_->GetTotalWaveCount());

    pHealth.setString(health);
    pMoney.setString(money);
    waves.setString(waveText);

    pHealth.setCharacterSize(20);
    pMoney.setCharacterSize(20);
    waves.setCharacterSize(20);

    pHealth.setFillColor(sf::Color::Red);
    pMoney.setFillColor(sf::Color::Green);
    waves.setFillColor(sf::Color::White);



    pHealth.setPosition(1060,450);
    pMoney.setPosition(1060, 485);
    waves.setPosition(1060, 520);

    window_.draw(pHealth);
    window_.draw(pMoney);
    window_.draw(waves);
}

void GameState::draw_selected_tower_info() {
    if (!isTowerSelected) return;

    draw_tower_range(selectedTower_.x, selectedTower_.y, selectedTower_.tower->GetTower());
    auto globals = gui_->getGlobalObjects();

    auto tower = selectedTower_.tower->GetTower();

    auto &sprite = globals->getTowerSpriteByType(tower->getType());
    sprite.setScale(6, 6);
    sprite.setPosition(50, 550);

    sf::Text name, description, range, strength;
    std::vector<sf::Text*> c = {&name, &description, &range, &strength};
    for (int i = 0; i < c.size(); i++) {
        auto d = c[i];
        d->setCharacterSize(15);
        d->setPosition(180, 550 + i * 30);
        d->setFont(getFont());
    }
    auto desc = tower->GetDescription();
    int numberOfNewLines = std::count(desc.begin(), desc.end(), '\n');

    name.setString("Name: " + tower->GetName());
    description.setString("Description: \n\n" + desc);
    range.setString("Range: " + std::to_string(tower->GetRange()));
    range.setPosition(180, 640 + numberOfNewLines * 20);
    strength.setString("Strength: " + std::to_string(tower->GetStrength()));
    strength.setPosition(180, 660 + numberOfNewLines * 20);
    if(tower->GetMainType() == "attack") {
        auto att = (AttackTower*)tower;
        strength.setString("Cooldown: " + std::to_string(att->GetCooldownLimit()));
        strength.setPosition(180, 680 + numberOfNewLines * 20);
    }


    window_.draw(sprite);
    window_.draw(name);
    for (auto e : c) {
        window_.draw(*e);

    }

}
void GameState::add_popup(const std::string& content, int posX, bool permanent) {
    auto text = new sf::Text();
    text->setString(content);
    text->setFont(getFont());
    text->setCharacterSize(20);
    text->setOutlineColor(Color::Black);
    text->setOutlineThickness(3);
    text->setPosition(posX, 40);

   remove_popup();

    popupText_.text = text;
    popupText_.permanent = permanent;
    popupText_.opacity = 1;
}
void GameState::remove_popup() {
    delete popupText_.text;
    popupText_.text = nullptr;
    popupText_.permanent = false;
    popupText_.opacity = 1;
}

void GameState::draw_popup_text() {
    if (popupText_.text == nullptr) return;
    if (!popupText_.permanent) {popupText_.opacity -= 0.005;}
    if (popupText_.opacity <= 0) {
        remove_popup();
        return;
    }
    popupText_.text->setFillColor(Color(255, 255, 255, popupText_.opacity * 255));
    popupText_.text->setOutlineColor(Color(0, 0, 0, popupText_.opacity * 255));
    window_.draw(*popupText_.text);


}


