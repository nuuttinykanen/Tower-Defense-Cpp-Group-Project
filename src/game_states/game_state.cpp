#include "../Gui.h"
#include "game_state.h"
#include "menu_state.h"


#define TOWER_BUTTON_GRID_START_X 1050
#define TOWER_BUTTON_GRID_START_Y 75


GameState::GameState(sf::RenderWindow &window, Gui* gui, int levelNumber)
: levelNumber_(levelNumber), WindowState(window, gui) {

    generateButtons();
    generateEnemies();
    generateTowers();
    generateProjectiles();

    auto waves = JSON::loadWaves(levelNumber);
    levelMap_ = JSON::loadLevelMap(levelNumber);
    Bomber* b = new Bomber();
    Gunner* g = new Gunner();
    levelMap_->PlaceTower(9, 8, b);
    levelMap_->PlaceTower(11, 3, g);
    player_ = new Player(100);
    game_ = new Game( *levelMap_, *player_, waves);
    auto towerShop_ = std::vector<Tower*>();
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

    sf::CircleShape shape(35);
    sf::Color color = sf::Color::White;
    color.a = 50;
    shape.setOutlineThickness(1);
    sf::Color outline_color = sf::Color::Black;
    outline_color.a = 60;
    shape.setOutlineColor(outline_color);
    shape.setScale(tow->GetRange(), tow->GetRange());
    shape.setFillColor(color);
    shape.setPosition((tsq->GetX() - tow->GetRange() + 0.5) * 35, (tsq->GetY() - tow->GetRange() + 0.5) * 35);
    window_.draw(shape);
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

        draw_tower_range(it.second);
        sf::Sprite tow_sprite = towerSprites_.at(it.second->GetTower()->GetName());
        tow_sprite.setScale(1.9,1.9);
        tow_sprite.setPosition(it.second->GetX() * 35, it.second->GetY() * 35);
        window_.draw(tow_sprite);

    }
    for(auto it : map.GetEnemySquares()) {
        if(it.second->ContainsEnemies()) {
            for(Enemy* en : it.second->GetEnemies()) {
                sf::Sprite en_sprite = enemySprites_.at(en->GetName());
                en_sprite.setScale(2, 2);
                en_sprite.setPosition(it.second->GetX()*35, it.second->GetY()*35);
                window_.draw(en_sprite);
            }
        }
    }

    // Draw projectiles
    for(auto it : map.GetProjectiles()) {
        if(it->GetLocation() != nullptr && it->GetSender() != nullptr) {
            auto projSprite = projectileSprites_.at(it->GetSender()->GetName());
            projSprite.setScale(1.5,1.5);
            projSprite.setPosition(it->GetLocation()->GetX() * 35.5, it->GetLocation()->GetY()* 35.5);
            window_.draw(projSprite);
        }
    }
}

void GameState::poll_events() {
    sf::Event event{};

    while (window_.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window_.close();

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

                        case Attack1: {
                            auto newTower = new Gunner();
                            if(newTower->GetPrice() <= player_->GetMoney()) {
                                buyTower(newTower);
                                std::cout << "Choosing tower!" << std::endl;
                            } else {
                                std::cout << "You don't have enough money!" << std::endl;
                                delete (newTower);
                            }
                            return;
                        }
                        case Attack2: {
                            auto newTower = new Bomber();
                            if(newTower->GetPrice() <= player_->GetMoney()) {
                                buyTower(newTower);
                                std::cout << "Choosing tower!" << std::endl;
                            } else {
                                std::cout << "You don't have enough money!" << std::endl;
                                delete (newTower);
                            }
                            return;
                        }
                        case Attack3: {
                            auto newTower = new Gunner();
                            if(newTower->GetPrice() <= player_->GetMoney()) {
                                buyTower(newTower);
                                std::cout << "Choosing tower!" << std::endl;
                            } else {
                                std::cout << "You don't have enough money!" << std::endl;
                                delete (newTower);
                            }
                            return;
                        }
                        case Attack4: {
                            auto newTower = new Gunner();
                            if(newTower->GetPrice() <= player_->GetMoney()) {
                                buyTower(newTower);
                                std::cout << "Choosing tower!" << std::endl;
                            } else {
                                std::cout << "You don't have enough money!" << std::endl;
                                delete (newTower);
                            }
                            return;
                        }
                        case Support1: {
                            auto newTower = new Gunner();
                            if(newTower->GetPrice() <= player_->GetMoney()) {
                                buyTower(newTower);
                                std::cout << "Choosing tower!" << std::endl;
                            } else {
                                std::cout << "You don't have enough money!" << std::endl;
                                delete (newTower);
                            }
                            return;
                        }
                        case Support2: {
                            auto newTower = new Gunner();
                            if(newTower->GetPrice() <= player_->GetMoney()) {
                                buyTower(newTower);
                                std::cout << "Choosing tower!" << std::endl;
                            } else {
                                std::cout << "You don't have enough money!" << std::endl;
                                delete (newTower);
                            }
                            return;
                        }
                        case Support3: {
                            auto newTower = new Gunner();
                            if(newTower->GetPrice() <= player_->GetMoney()) {
                                buyTower(newTower);
                                std::cout << "Choosing tower!" << std::endl;
                            } else {
                                std::cout << "You don't have enough money!" << std::endl;
                                delete (newTower);
                            }
                            return;
                        }
                        case Support4: {
                            auto newTower = new Gunner();
                            if(newTower->GetPrice() <= player_->GetMoney()) {
                                buyTower(newTower);
                                std::cout << "Choosing tower!" << std::endl;
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
    std::cout << "Quitting to menu!" << std::endl;
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
    auto attack1Button = new TowerButton(sf::Vector2f(TOWER_BUTTON_GRID_START_X, TOWER_BUTTON_GRID_START_Y), gui_->getGlobalObjects()->getTowerSquareSprite());
    towerButtons_[TowerSelectionTarget::Attack1] = attack1Button;

    auto attack2Button = new TowerButton(sf::Vector2f(TOWER_BUTTON_GRID_START_X + 100, TOWER_BUTTON_GRID_START_Y), gui_->getGlobalObjects()->getTowerSquareSprite());
    towerButtons_[TowerSelectionTarget::Attack2] = attack2Button;

    auto attack3Button = new TowerButton(sf::Vector2f(TOWER_BUTTON_GRID_START_X, TOWER_BUTTON_GRID_START_Y + 100), gui_->getGlobalObjects()->getTowerSquareSprite());
    towerButtons_[TowerSelectionTarget::Attack3] = attack3Button;

    auto attack4Button = new TowerButton(sf::Vector2f(TOWER_BUTTON_GRID_START_X + 100, TOWER_BUTTON_GRID_START_Y + 100), gui_->getGlobalObjects()->getTowerSquareSprite());
    towerButtons_[TowerSelectionTarget::Attack4] = attack4Button;

    auto support1Button = new TowerButton(sf::Vector2f(TOWER_BUTTON_GRID_START_X, TOWER_BUTTON_GRID_START_Y + 200), gui_->getGlobalObjects()->getTowerSquareSprite());
    towerButtons_[TowerSelectionTarget::Support1] = support1Button;

    auto support2Button = new TowerButton(sf::Vector2f(TOWER_BUTTON_GRID_START_X + 100, TOWER_BUTTON_GRID_START_Y + 200), gui_->getGlobalObjects()->getTowerSquareSprite());
    towerButtons_[TowerSelectionTarget::Support2] = support2Button;

    auto support3Button = new TowerButton(sf::Vector2f(TOWER_BUTTON_GRID_START_X, TOWER_BUTTON_GRID_START_Y + 300), gui_->getGlobalObjects()->getTowerSquareSprite());
    towerButtons_[TowerSelectionTarget::Support3] = support3Button;

    auto support4Button = new TowerButton(sf::Vector2f(TOWER_BUTTON_GRID_START_X + 100, TOWER_BUTTON_GRID_START_Y + 300), gui_->getGlobalObjects()->getTowerSquareSprite());
    towerButtons_[TowerSelectionTarget::Support4] = support4Button;
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
    projectileSprites_["Bomber"] = gui_->getGlobalObjects()->getBombProjecSprite();
    projectileSprites_["Gunner"] = gui_->getGlobalObjects()->getGunProjecSprite();
    projectileSprites_["Super Bomber"] = gui_->getGlobalObjects()->getGunProjecSprite();
}
