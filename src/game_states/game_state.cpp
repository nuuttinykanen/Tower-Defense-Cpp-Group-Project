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
        if (!JSON::latestSaveExists() && levelNumber == 0) {
            levelNumber_ = 1;
        } else {
            levelNumber_ = levelNumber;
        }
        levelMap_ = JSON::loadLevelMap(levelNumber_);
        auto waves = JSON::loadWaves(levelNumber_);
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

void GameState::draw_tower_range(TowerSquare* tsq) {
    Tower* tow = tsq->GetTower();
    if(tow == nullptr) return;

    for(auto it : levelMap_->GetSquares()) {
        double tx = tsq->GetX();
        double ty = tsq->GetY();
        double x = it.first.first;
        double y = it.first.second;
        if(sqrt(pow(tx - x, 2.0) + pow(ty - y, 2.0)) <= tsq->GetTower()->GetRange()) {
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

void GameState::draw_current_state() {
    for (auto b : buttons_) {
        switch (b.first) {
            case UpgradeTower:
                if (!isTowerSelected) continue;
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

    }
    for(auto it : map.GetEnemySquares()) {
        if(it.second->ContainsEnemies()) {
            for(Enemy* en : it.second->GetEnemies()) {
                sf::Sprite en_sprite = enemySprites_.at(en->GetName());
                en_sprite.setScale(2, 2);
                en_sprite.setPosition(it.second->GetX()*35, it.second->GetY()*35);
                window_.draw(en_sprite);

                sf::RectangleShape outer(sf::Vector2f(19, 4));
                outer.setSize(sf::Vector2f(20, 2));
                outer.setOutlineColor(sf::Color::White);
                outer.setFillColor(sf::Color::Transparent);
                outer.setPosition(it.second->GetX()*35, it.second->GetY()*35);
                window_.draw(outer);


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


}

bool buyingTower = false;
bool sellingTower = false;
Tower* newTower = nullptr;
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
                    buyingTower = !(this->levelMap_->PlaceTower(area.second->GetX(), area.second->GetY(), newTower));
                    buyTower(newTower);
                    break;
                }
            }
        }

        //sells and removes a tower from a tower square
        if (sellingTower && event.type == sf::Event::MouseButtonReleased) {
            auto removeFrom = window_.mapPixelToCoords(sf::Mouse::getPosition(window_));
            for(auto area : map.GetTowerSquares()) {
                auto freeSprite = globals->getFreeSquareSprite();
                freeSprite.setScale(2, 2);
                freeSprite.setPosition(area.second->GetX() * 35, area.second->GetY() * 35);
                if(freeSprite.getGlobalBounds().contains(removeFrom)) {
                    try {
                        Tower* soldTower = this->levelMap_->TowerAt(area.second->GetX(), area.second->GetY());
                        sellingTower = !(this->levelMap_->EraseTower(soldTower));
                        sellTower(soldTower);
                    } catch(std::invalid_argument) {
                        break;
                    }
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
                            return;
                        case StartWave:
                            buyingTower = false;
                            sellingTower = false;
                            startWave();
                            return;
                        case SellTower:
                            buyingTower = false;
                            sellingTower = true;
                            std::cout << "Click on a tower to sell it!" << std::endl;
                            return;
                        case UpgradeTower:
                            buyingTower = false;
                            sellingTower = false;
                            return;
                        case DeselectTower:
                            isTowerSelected = false;
                            return;
                    }
                }
                for (auto t : towerButtons_) {
                    if (!t.second->contains(mouse_pos)) continue;
                    switch (t.first) {

                        case GunnerType: {
                            newTower = new Gunner();
                            if(newTower->GetPrice() <= player_->GetMoney()) {
                                std::cout << "Choosing tower!" << std::endl;
                                std::cout << "Click on a free square to place the tower!" << std::endl;
                                buyingTower = true;
                            } else {
                                std::cout << "You don't have enough money!" << std::endl;
                                delete (newTower);
                            }

                            return;
                        }
                        case BomberType: {
                            newTower = new Bomber();
                            if(newTower->GetPrice() <= player_->GetMoney()) {
                                std::cout << "Choosing tower!" << std::endl;
                                std::cout << "Click on a free square to place the tower!" << std::endl;
                                buyingTower = true;
                            } else {
                                std::cout << "You don't have enough money!" << std::endl;
                                delete (newTower);
                            }

                            return;
                        }
                        case Attack3: {
                            newTower = new Gunner();
                            if(newTower->GetPrice() <= player_->GetMoney()) {
                                std::cout << "Choosing tower!" << std::endl;
                                std::cout << "Click on a free square to place the tower!" << std::endl;
                                buyingTower = true;
                            } else {
                                std::cout << "You don't have enough money!" << std::endl;
                                delete (newTower);
                            }

                            return;
                        }
                        case Attack4: {
                            newTower = new Gunner();
                            if(newTower->GetPrice() <= player_->GetMoney()) {
                                std::cout << "Choosing tower!" << std::endl;
                                std::cout << "Click on a free square to place the tower!" << std::endl;
                                buyingTower = true;
                            } else {
                                std::cout << "You don't have enough money!" << std::endl;
                                delete (newTower);
                            }

                            return;
                        }
                        case ClockerType: {
                            newTower = new Clocker();
                            if(newTower->GetPrice() <= player_->GetMoney()) {
                                std::cout << "Choosing tower!" << std::endl;
                                std::cout << "Click on a free square to place the tower!" << std::endl;
                                buyingTower = true;
                            } else {
                                std::cout << "You don't have enough money!" << std::endl;
                                delete (newTower);
                            }

                            return;
                        }
                        case SeerType: {
                            newTower = new Seer();
                            if(newTower->GetPrice() <= player_->GetMoney()) {
                                std::cout << "Choosing tower!" << std::endl;
                                std::cout << "Click on a free square to place the tower!" << std::endl;
                                buyingTower = true;
                            } else {
                                std::cout << "You don't have enough money!" << std::endl;
                                delete (newTower);
                            }

                            return;
                        }
                        case StereoType: {
                            newTower = new StereoDude();
                            if(newTower->GetPrice() <= player_->GetMoney()) {
                                std::cout << "Choosing tower!" << std::endl;
                                std::cout << "Click on a free square to place the tower!" << std::endl;
                                buyingTower = true;
                            } else {
                                std::cout << "You don't have enough money!" << std::endl;
                                delete (newTower);
                            }

                            return;
                        }
                        case Support4: {
                            newTower = new Clocker();
                            if(newTower->GetPrice() <= player_->GetMoney()) {
                                std::cout << "Choosing tower!" << std::endl;
                                std::cout << "Click on a free square to place the tower!" << std::endl;
                                buyingTower = true;
                            } else {
                                std::cout << "You don't have enough money!" << std::endl;
                                delete (newTower);
                            }

                            return;
                        }
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
}

void GameState::quitToMenu() {
    saveGame();
    gui_->change_game_state(new MenuState(window_, gui_));
}

void GameState::startWave() {
    game_->StartWave();
    isTowerSelected = false;
    if (!game_->ifWaveInProgress()) {
        // Remove the start wave button
        for (auto it = buttons_.begin(); it != buttons_.end(); it++) {
            if (it->first == GameButtonTarget::StartWave) {
                delete it->second;
                buttons_.erase(it);
            }
        }
    }
}

void GameState::buyTower(Tower* tower) {
    player_->AddTower(tower);
    std::cout << "Tower bought successfully!" << std::endl;
}

void GameState::sellTower(Tower* tower) {
    player_->SellTower(tower);
    std::cout << "Tower sold successfully!" << std::endl;
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
    projectileHitSprites_["bullet"] = gui_->getGlobalObjects()->getGunProjecHitSprite();
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

    draw_tower_range(selectedTower_.tower);
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

    c[0]->setString("Name: " + tower->GetName());
    c[1]->setString("Description: " + tower->GetDescription());
    c[2]->setString("Range: " + std::to_string(tower->GetRange()));
    c[3]->setString("Strength: " + std::to_string(tower->GetStrength()));


    window_.draw(sprite);
    window_.draw(name);
    for (auto e : c) {
        window_.draw(*e);

    }

}
