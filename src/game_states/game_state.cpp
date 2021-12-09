#include "../Gui.h"
#include "game_state.h"
#include "menu_state.h"
#include <cmath>

#define TOWER_BUTTON_GRID_START_X 1050
#define TOWER_BUTTON_GRID_START_Y 75


GameState::GameState(sf::RenderWindow &window, Gui* gui, int levelNumber): WindowState(window, gui) {

    generateButtons();
    generateEnemies();
    generateTowers();
    generateProjectiles();
    generateProjectileHitSprites();

    // 0 level number means that we are loading the latest save
    if (levelNumber == 0) {
        game_ = JSON::loadLatestSave();
        levelMap_ = &game_->GetMap();
        levelNumber_ = levelMap_->getLevelNumber();
        player_ = &game_->GetPlayer();

    } else {
        levelNumber_ = levelNumber;
        levelMap_ = JSON::loadLevelMap(levelNumber);
        auto waves = JSON::loadWaves(levelNumber);
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

void GameState::draw_tower_range(LevelMap* map, TowerSquare* tsq) {
    Tower* tow = tsq->GetTower();
    if(tow == nullptr) return;

    for(auto it : map->GetSquares()) {
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
        b.second->draw(window_);
    }
    for (auto t : towerButtons_)  {
        t.second->draw(window_);
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

    //Draw player health and money ///////////////////////////////////////////
    sf::Text pHealth;
    sf::Text pMoney;

    pHealth.setFont(this->getFont());
    pMoney.setFont(this->getFont());

    std::string health = "Health: " + std::to_string(this->player_->GetHealth());
    std::string money = "Money: " + std::to_string(int(this->player_->GetMoney()));

    pHealth.setString(health);
    pMoney.setString(money);

    pHealth.setCharacterSize(32);
    pMoney.setCharacterSize(32);

    pHealth.setFillColor(sf::Color::Red);
    pMoney.setFillColor(sf::Color::Green);

    pHealth.setPosition(10,550);
    pMoney.setPosition(10, 600);

    window_.draw(pHealth);
    window_.draw(pMoney);

    // Draw towers
    for(auto it : map.GetTowerSquares()) {

        auto freeSprite = globals->getFreeSquareSprite();
        freeSprite.setScale(2, 2);
        freeSprite.setPosition(it.second->GetX()*35, it.second->GetY()*35);
        window_.draw(freeSprite);

        for(auto sq : it.second->EnemySquaresInRange()) {
            sf::Sprite r_sprite = globals->getRangeSprite();
            r_sprite.setScale(2,2);
            r_sprite.setPosition(sq->GetX() * 35, sq->GetY()* 35);
            window_.draw(r_sprite);
        }


        sf::Sprite tow_sprite = towerSprites_.at(it.second->GetTower()->GetName());
        tow_sprite.setScale(1.9,1.9);
        tow_sprite.setPosition(it.second->GetX() * 35, it.second->GetY() * 35);
        draw_tower_range(levelMap_, it.second);
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
Tower* newTower = nullptr;
void GameState::poll_events() {
    sf::Event event{};
    LevelMap& map = game_->GetMap();
    auto globals = gui_->getGlobalObjects();
    while (window_.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window_.close();

        // 0 -> primary click, 1-> secondary

        if (buyingTower && event.type == sf::Event::MouseButtonReleased) {
            auto placeTo = window_.mapPixelToCoords(sf::Mouse::getPosition(window_));
            for(auto area : map.GetFreeSquares()) {
                auto freeSprite = globals->getFreeSquareSprite();
                freeSprite.setScale(2, 2);
                freeSprite.setPosition(area.second->GetX() * 35, area.second->GetY() * 35);
                if(freeSprite.getGlobalBounds().contains(placeTo)) {
                    buyingTower = !(this->levelMap_->PlaceTower(area.second->GetX(), area.second->GetY(), newTower));
                    if(buyingTower) {
                        std::cout << "Choose another square!" << std::endl;
                    } else {
                        buyTower(newTower);
                    }
                    break;
                }
            }
        }

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
                            startWave();
                            return;
                        case SellTower:
                            return;
                        case UpgradeTower:
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
}

void GameState::generateButtons() {
    // Generate buttons
    auto startButton = new Button(sf::Vector2f (225, 50), sf::Vector2f(1050, 650),
                                  "Quit game",this->getFont(), 20);
    buttons_[GameButtonTarget::QuitToMenu] = startButton;
    auto startWaveButton = new Button(sf::Vector2f(225, 50), sf::Vector2f(1050, 590),
                                      "Start wave!", this->getFont(), 20);
    buttons_[GameButtonTarget::StartWave] = startWaveButton;
    auto upgradeTowerButton = new Button(sf::Vector2f(275, 50), sf::Vector2f(750
                                                 , 590),
                                         "Upgrade tower", this->getFont(), 20);
    buttons_[GameButtonTarget::UpgradeTower] = upgradeTowerButton;

    auto sellTowerButton = new Button(sf::Vector2f(275, 50), sf::Vector2f(750, 650),
                                      "Sell tower", this->getFont(), 20);
    buttons_[GameButtonTarget::SellTower] = sellTowerButton;

    // TODO: Add the correct sprites here when they are made
    auto attack1Button = new TowerButton(sf::Vector2f(TOWER_BUTTON_GRID_START_X, TOWER_BUTTON_GRID_START_Y), gui_->getGlobalObjects()->getGunnerSprite());
    towerButtons_[TowerTypes::GunnerType] = attack1Button;

    auto attack2Button = new TowerButton(sf::Vector2f(TOWER_BUTTON_GRID_START_X + 100, TOWER_BUTTON_GRID_START_Y), gui_->getGlobalObjects()->getBomberSprite());
    towerButtons_[TowerTypes::BomberType] = attack2Button;

    auto attack3Button = new TowerButton(sf::Vector2f(TOWER_BUTTON_GRID_START_X, TOWER_BUTTON_GRID_START_Y + 100), gui_->getGlobalObjects()->getGunnerSprite());
    towerButtons_[TowerTypes::Attack3] = attack3Button;

    auto attack4Button = new TowerButton(sf::Vector2f(TOWER_BUTTON_GRID_START_X + 100, TOWER_BUTTON_GRID_START_Y + 100), gui_->getGlobalObjects()->getGunnerSprite());
    towerButtons_[TowerTypes::Attack4] = attack4Button;

    auto support1Button = new TowerButton(sf::Vector2f(TOWER_BUTTON_GRID_START_X, TOWER_BUTTON_GRID_START_Y + 200), gui_->getGlobalObjects()->getClockerSprite());
    towerButtons_[TowerTypes::ClockerType] = support1Button;

    auto support2Button = new TowerButton(sf::Vector2f(TOWER_BUTTON_GRID_START_X + 100, TOWER_BUTTON_GRID_START_Y + 200), gui_->getGlobalObjects()->getSeerSprite());
    towerButtons_[TowerTypes::SeerType] = support2Button;

    auto support3Button = new TowerButton(sf::Vector2f(TOWER_BUTTON_GRID_START_X, TOWER_BUTTON_GRID_START_Y + 300), gui_->getGlobalObjects()->getStereoDudeSprite());
    towerButtons_[TowerTypes::StereoType] = support3Button;

    auto support4Button = new TowerButton(sf::Vector2f(TOWER_BUTTON_GRID_START_X + 100, TOWER_BUTTON_GRID_START_Y + 300), gui_->getGlobalObjects()->getGunnerSprite());
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
