#include "../gui.h"
#include "game_state.h"
#include "menu_state.h"
#include <cmath>

#define TOWER_BUTTON_GRID_START_X 1065
#define TOWER_BUTTON_GRID_START_Y 15
#define TOWER_BUTTON_OFFSET 110



GameState::GameState(sf::RenderWindow &window, Gui* gui, int level_number): WindowState(window, gui) {

    GenerateButtons();
    GenerateEnemies();
    GenerateTowers();
    GenerateProjectiles();
    GenerateProjectileHitSprites();

    // 0 level number means that we are loading the latest save, also check that the file exists
    if (level_number == 0 && JSON::LatestSaveExists()) {
        game_ = JSON::LoadLatestSave();
        level_map_ = &game_->GetMap();
        level_number_ = level_map_->getLevelNumber();
        player_ = &game_->GetPlayer();

    } else {
        if (!JSON::LatestSaveExists() && level_number == 0) { level_number_ = 1;}
        else { level_number_ = level_number;}

        level_map_ = JSON::LoadLevelMap(level_number_);
        auto waves = JSON::LoadWaves(level_number_);
        player_ = new Player(100);
        game_ = new Game(*level_map_, *player_, waves);
    }
}
GameState::~GameState() {
    for (auto b : buttons_) {
        delete b.second;
    }
    for (auto t : tower_buttons_) {
        delete t.second;
    }
}

void GameState::AdvanceState() {
    game_->UpdateState();
}

void GameState::DrawTowerRange(int tx, int ty, Tower* tow) {
    if(tow == nullptr) return;

    for(auto it : level_map_->GetSquares()) {
        double x = it.first.first;
        double y = it.first.second;
        if(sqrt(pow(tx - x, 2.0) + pow(ty - y, 2.0)) <= tow->GetRange()) {
            sf::RectangleShape rectangle(sf::Vector2f(1, 1));
            rectangle.setSize(sf::Vector2f(35, 35));
            rectangle.setPosition(x * 35, y * 35);
            rectangle.setOutlineThickness(1);
            rectangle.setOutlineColor(sf::Color::Black);
            sf::Color color;
            if(it.second->GetType() == "enemy") {
                color = sf::Color::Magenta;
            }
            else {
                    color = sf::Color::White;
                    color.a = 90;
            }
            rectangle.setFillColor(color);
            window_.draw(rectangle);
        }
    }
}

bool buyingTower = false;
Tower* newTower = nullptr;

void GameState::DrawCurrentState() {
    for (auto b : buttons_) {
        switch (b.first) {
            case UpgradeTowerTarget:
                if (!is_tower_selected || !selected_tower_.canUpgrade) continue;
                break;
            case SellTowerTarget:
                if (!is_tower_selected) continue;
                break;
            case DeselectTowerTarget:
                if (!is_tower_selected) continue;
                break;
            default:
                break;
        }
        b.second->draw(window_);
    }
    for (auto t : tower_buttons_)  {
        t.second->draw(window_, player_->GetMoney());
    }
    auto globals = gui_->GetGlobalObjects();

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

    DrawPlayerInfo();

    // Draw purchase candidate tower info and range.
    if (newTower != nullptr && buyingTower) {
        DrawTowerInfo(newTower);
        auto mouse_pos = window_.mapPixelToCoords(sf::Mouse::getPosition(window_));
        for (auto area: map.GetSquares()) {
            auto freeSprite = this->tower_sprites_.at(newTower->GetName());
            freeSprite.setScale(2, 2);
            freeSprite.setPosition(area.second->GetX() * 35, area.second->GetY() * 35);
            if (freeSprite.getGlobalBounds().contains(mouse_pos)) {
                DrawTowerRange(area.second->GetX(), area.second->GetY(), newTower);
                window_.draw(freeSprite);
                break;
            }
        }
    }
    else if(is_tower_selected) {
        for(auto b : buttons_) {
        }
        DrawTowerInfo(selected_tower_.tower->GetTower());
        DrawTowerRange(selected_tower_.x, selected_tower_.y, selected_tower_.tower->GetTower());
    }

    // Draw towers
    for(auto it : map.GetTowerSquares()) {

        auto freeSprite = globals->getFreeSquareSprite();
        freeSprite.setScale(2, 2);
        freeSprite.setPosition(it.second->GetX()*35, it.second->GetY()*35);
        window_.draw(freeSprite);


        sf::Sprite tow_sprite = tower_sprites_.at(it.second->GetTower()->GetName());
        tow_sprite.setScale(1.9,1.9);
        tow_sprite.setPosition(it.second->GetX() * 35, it.second->GetY() * 35);

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
                sf::Sprite en_sprite = enemy_sprites_.at(en->GetName());
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
            auto sprite = this->projectile_hit_sprites_[it.first];
            sprite.setScale(2, 2);
            sprite.setPosition(coords.first * 35, coords.second * 35);
            window_.draw(sprite);
        }
    }

    // Draw projectiles
    for(auto it : map.GetProjectiles()) {
        if(it->GetLocation() != nullptr && it->GetSender() != nullptr) {
            auto projSprite = projectile_sprites_.at(it->GetSender()->GetName());
            projSprite.setScale(0.2,0.2);
            projSprite.setPosition(it->GetLocation()->GetX() * 35.5, it->GetLocation()->GetY()* 35.5);
            window_.draw(projSprite);
        }
    }

    DrawPopupText();

}


void GameState::PollEvents() {
    sf::Event event{};
    LevelMap& map = game_->GetMap();
    auto globals = gui_->GetGlobalObjects();
    while (window_.pollEvent(event))
    {
        if (event.type == sf::Event::Closed) {
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
                    this->level_map_->PlaceTower(area.second->GetX(), area.second->GetY(), newTower);
                    buyingTower = false;
                    RemovePopup();
                    BuyTower(newTower);
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
                    if (!b.second->contains(mouse_pos)) {
                        continue;
                    }
                    switch (b.first) {

                        case QuitToMenuTarget:
                            QuitToMenu();
                            return;
                        case SaveGameTarget:
                            if (game_->isWaveInProgress()) {
                                AddPopup("Can't save while in the middle of a wave!", 200, false);
                            } else {
                                SaveGame();
                                AddPopup("Game saved!", 400, false);
                            }
                            return;
                        case StartWaveTarget:
                            buyingTower = false;
                            RemovePopup();
                            StartWave();
                            return;
                        case SellTowerTarget:
                            if(buyingTower || !is_tower_selected) return;
                            RemovePopup();
                            SellTower();
                            return;
                        case UpgradeTowerTarget:
                            if(buyingTower || !is_tower_selected) return;
                            RemovePopup();
                            UpgradeTower();
                            return;
                        case DeselectTowerTarget:
                            is_tower_selected = false;
                            return;
                        default:
                            is_tower_selected = false;
                            buyingTower = false;
                            return;
                    }
                }

                for (auto t : tower_buttons_) {
                    if (!t.second->contains(mouse_pos)) continue;

                    newTower = GetTowerByType(t.first);

                    if(newTower->GetPrice() <= player_->GetMoney()) {
                        AddPopup("Place the " + newTower->GetName() + " in a free square!", 185, true);
                        buyingTower = true;
                    } else {
                        AddPopup("You don't have enough money!", 200, false);
                        delete newTower;
                    }

                }
                for(auto area : map.GetTowerSquares()) {
                    auto freeSprite = globals->getFreeSquareSprite();
                    freeSprite.setScale(2, 2);
                    freeSprite.setPosition(area.second->GetX() * 35, area.second->GetY() * 35);
                    if(freeSprite.getGlobalBounds().contains(mouse_pos)) {
                        if (selected_tower_.tower == area.second) {
                            is_tower_selected = false;
                            selected_tower_.tower = nullptr;
                            break;
                        }
                        is_tower_selected = true;
                        selected_tower_.tower = area.second;
                        selected_tower_.canUpgrade = area.second->GetTower()->CanUpgrade();
                        selected_tower_.x = area.second->GetX();
                        selected_tower_.y = area.second->GetY();
                        break;
                    }
                }
            } else if (event.mouseButton.button == 1) {
                is_tower_selected = false;
            }

        }
    }
    if (game_->isGameOver()) {
        auto newState = new FinishState(window_, gui_, level_number_);

        gui_->ChangeGameState(newState);
        return;
    }
}

void GameState::QuitToMenu() {
    gui_->ChangeGameState(new MenuState(window_, gui_));
}

void GameState::StartWave() {
    if (game_->isWaveInProgress()) {
        AddPopup("Can't start a new wave yet!", 200, false);
        return;
    }
    is_tower_selected = false;
    game_->StartWave();
    AddPopup("Starting wave " + std::to_string(game_->GetWaveNumber()), 350, false);

}

void GameState::BuyTower(Tower* tower) {
    player_->AddTower(tower);
}

void GameState::SellTower() {
    is_tower_selected = false;
    auto tower = selected_tower_.tower->GetTower();
    game_->SellTower(selected_tower_.tower);
    this->level_map_->EraseTowerAt(selected_tower_.tower);

    player_->SellTower(tower);

}

void GameState::UpgradeTower() {
    if (selected_tower_.tower != nullptr && selected_tower_.tower->GetTower()->CanUpgrade()) {
        auto upgrade = selected_tower_.tower->GetTower()->Upgrade();
        if(upgrade != nullptr) {
            if(upgrade->GetPrice() > player_->GetMoney()) {
                AddPopup("You don't have enough money!", 200, false);
                delete(upgrade);
            } else {
                player_->AddTower(upgrade);
                int x = selected_tower_.tower->GetX();
                int y = selected_tower_.tower->GetY();
                this->level_map_->EraseTowerAt(selected_tower_.tower);
                this->level_map_->PlaceTower(x, y, upgrade);
                selected_tower_.tower = level_map_->FindTower(upgrade);
            }
        } else {
            AddPopup("No upgrade available!", 200, false);
        }
    }
}

void GameState::GenerateButtons() {
    // Generate buttons

    auto startWaveButton = new Button(sf::Vector2f(215, 40), sf::Vector2f(1060, 550),
                                      "Start wave!", this->GetFont(), 20, 2, 8);
    buttons_[GameButtonTarget::StartWaveTarget] = startWaveButton;

    auto saveButton = new Button(sf::Vector2f(215, 40), sf::Vector2f(1060, 610),
                                 "Save game", this->GetFont(), 20, 20, 8);
    buttons_[GameButtonTarget::SaveGameTarget] = saveButton;

    auto quitButton = new Button(sf::Vector2f (215, 40), sf::Vector2f(1060, 670),
                                 "Quit", this->GetFont(), 20, 18, 8);
    buttons_[GameButtonTarget::QuitToMenuTarget] = quitButton;

    auto upgradeTowerButton = new Button(sf::Vector2f(300, 40), sf::Vector2f(700
                                                 , 550),
                                         "Upgrade tower", this->GetFont(), 20, 18, 8);
    buttons_[GameButtonTarget::UpgradeTowerTarget] = upgradeTowerButton;

    auto sellTowerButton = new Button(sf::Vector2f(300, 40), sf::Vector2f(700, 610),
                                      "Sell tower", this->GetFont(), 20, 50, 8);
    buttons_[GameButtonTarget::SellTowerTarget] = sellTowerButton;
    auto deselectTowerButton = new Button(sf::Vector2f(300, 40), sf::Vector2f(700, 670),
                                          "Deselect tower", this->GetFont(), 20, 18, 8);
    buttons_[GameButtonTarget::DeselectTowerTarget] = deselectTowerButton;


    // TODO: Add the correct sprites here when they are made
    // TODO: Add correct costs in the end
    auto attack1Button = new TowerButton(sf::Vector2f(TOWER_BUTTON_GRID_START_X, TOWER_BUTTON_GRID_START_Y),
                                         gui_->GetGlobalObjects()->getGunnerSprite(),
                                         GetFont(), 50);
    tower_buttons_[TowerTypes::GunnerType] = attack1Button;

    auto attack2Button = new TowerButton(sf::Vector2f(TOWER_BUTTON_GRID_START_X + TOWER_BUTTON_OFFSET, TOWER_BUTTON_GRID_START_Y),
                                         gui_->GetGlobalObjects()->getKnifeBotSprite(),
                                         GetFont(), 100);
    tower_buttons_[TowerTypes::KnifeBotType] = attack2Button;

    auto attack3Button = new TowerButton(sf::Vector2f(TOWER_BUTTON_GRID_START_X, TOWER_BUTTON_GRID_START_Y + TOWER_BUTTON_OFFSET),
                                         gui_->GetGlobalObjects()->getBomberSprite(),
                                         GetFont(), 200);
    tower_buttons_[TowerTypes::BomberType] = attack3Button;

    auto attack4Button = new TowerButton(sf::Vector2f(TOWER_BUTTON_GRID_START_X + TOWER_BUTTON_OFFSET, TOWER_BUTTON_GRID_START_Y + TOWER_BUTTON_OFFSET),
                                         gui_->GetGlobalObjects()->getCursedKidSprite(),
                                         GetFont(), 400);
    tower_buttons_[TowerTypes::CursedKidType] = attack4Button;

    auto support1Button = new TowerButton(sf::Vector2f(TOWER_BUTTON_GRID_START_X, TOWER_BUTTON_GRID_START_Y + 2 * TOWER_BUTTON_OFFSET),
                                          gui_->GetGlobalObjects()->getClockerSprite(),
                                          GetFont(), 350);
    tower_buttons_[TowerTypes::ClockerType] = support1Button;

    auto support2Button = new TowerButton(sf::Vector2f(TOWER_BUTTON_GRID_START_X + TOWER_BUTTON_OFFSET, TOWER_BUTTON_GRID_START_Y + 2 * TOWER_BUTTON_OFFSET),
                                          gui_->GetGlobalObjects()->getSeerSprite(),
                                          GetFont(), 450);
    tower_buttons_[TowerTypes::SeerType] = support2Button;

    auto support3Button = new TowerButton(sf::Vector2f(TOWER_BUTTON_GRID_START_X, TOWER_BUTTON_GRID_START_Y + 3 * TOWER_BUTTON_OFFSET),
                                          gui_->GetGlobalObjects()->getStereoDudeSprite(),
                                          GetFont(), 400);
    tower_buttons_[TowerTypes::StereoType] = support3Button;

}

void GameState::GenerateEnemies() {
    enemy_sprites_["Zombie"] = gui_->GetGlobalObjects()->getZombieSprite();
    enemy_sprites_["Michael Myers"] = gui_->GetGlobalObjects()->getMichaelSprite();
    enemy_sprites_["Zombie Horde"] = gui_->GetGlobalObjects()->getHordeSprite();
    enemy_sprites_["Dracula"] = gui_->GetGlobalObjects()->getDraculaSprite();
    enemy_sprites_["Bat"] = gui_->GetGlobalObjects()->getBatSprite();
}

void GameState::GenerateTowers() {
    tower_sprites_["Bomber"] = gui_->GetGlobalObjects()->getBomberSprite();
    tower_sprites_["Gunner"] = gui_->GetGlobalObjects()->getGunnerSprite();
    tower_sprites_["Super Bomber"] = gui_->GetGlobalObjects()->getSuperBomberSprite();
    tower_sprites_["Ultra Bomber"]  = gui_->GetGlobalObjects()->getUltraBomberSprite();
    tower_sprites_["Stereo Dude"]  = gui_->GetGlobalObjects()->getStereoDudeSprite();
    tower_sprites_["DJ Dude"]  = gui_->GetGlobalObjects()->getDJDudeSprite();
    tower_sprites_["Seer"]  = gui_->GetGlobalObjects()->getSeerSprite();
    tower_sprites_["Mother Brain"]  = gui_->GetGlobalObjects()->getMotherBrainSprite();
    tower_sprites_["Clocker"]  = gui_->GetGlobalObjects()->getClockerSprite();
    tower_sprites_["Clock Blocker"]  = gui_->GetGlobalObjects()->getClockBlockerSprite();
    tower_sprites_["Multigunner"]  = gui_->GetGlobalObjects()->getMultigunnerSprite();
    tower_sprites_["Gun Fiend"]  = gui_->GetGlobalObjects()->getGunFiendSprite();
    tower_sprites_["Masked Kid"]  = gui_->GetGlobalObjects()->getMaskedKidSprite();
    tower_sprites_["Cursed Kid"]  = gui_->GetGlobalObjects()->getCursedKidSprite();
    tower_sprites_["Masked God"]  = gui_->GetGlobalObjects()->getMaskedGodSprite();
    tower_sprites_["Knife Bot"] = gui_->GetGlobalObjects()->getKnifeBotSprite();
    tower_sprites_["Knife Bot 2.0"] = gui_->GetGlobalObjects()->getKnifeBot2Sprite();
    tower_sprites_["Sword Bot"] = gui_->GetGlobalObjects()->getSwordBotSprite();
}

void GameState::GenerateProjectiles() {
    projectile_sprites_["Bomber"] = gui_->GetGlobalObjects()->getBomberSprite();
    projectile_sprites_["Gunner"] = gui_->GetGlobalObjects()->getGunnerSprite();
    projectile_sprites_["Super Bomber"] = gui_->GetGlobalObjects()->getSuperBomberSprite();
    projectile_sprites_["Ultra Bomber"]  = gui_->GetGlobalObjects()->getUltraBomberSprite();
    projectile_sprites_["Multigunner"]  = gui_->GetGlobalObjects()->getMultigunnerSprite();
    projectile_sprites_["Gun Fiend"]  = gui_->GetGlobalObjects()->getGunFiendSprite();
    projectile_sprites_["Masked Kid"]  = gui_->GetGlobalObjects()->getCursedProjectileSprite();
    projectile_sprites_["Cursed Kid"]  = gui_->GetGlobalObjects()->getCursedProjectileSprite();
    projectile_sprites_["Masked God"]  = gui_->GetGlobalObjects()->getCursedProjectileSprite();
    projectile_sprites_["Knife Bot"]  = gui_->GetGlobalObjects()->getCursedProjectileSprite();
    projectile_sprites_["Knife Bot 2.0"]  = gui_->GetGlobalObjects()->getCursedProjectileSprite();
    projectile_sprites_["Sword Bot"]  = gui_->GetGlobalObjects()->getCursedProjectileSprite();
}

void GameState::GenerateProjectileHitSprites() {
    projectile_hit_sprites_["bomb"] = gui_->GetGlobalObjects()->getBombProjecHit1Sprite();
    projectile_hit_sprites_["bullet"] = gui_->GetGlobalObjects()->getBombProjecHit2Sprite();
    projectile_hit_sprites_["cursed"] = gui_->GetGlobalObjects()->getCursedProjectileHitSprite();
}

void GameState::SaveGame() {
    JSON::SaveCurrentGame(game_, level_number_);
}

void GameState::DrawPlayerInfo() {
    sf::Text pHealth;
    sf::Text pMoney;
    sf::Text waves;

    pHealth.setFont(this->GetFont());
    pMoney.setFont(this->GetFont());
    waves.setFont(this->GetFont());

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

void GameState::DrawTowerInfo(Tower* tow) {
    if ((!is_tower_selected && newTower == nullptr)) return;
    auto globals = gui_->GetGlobalObjects();

    auto &sprite = globals->getTowerSpriteByType(tow->getType());
    sprite.setScale(6, 6);
    sprite.setPosition(50, 550);

    sf::Text name, description, range, strength, cooldown;
    std::vector<sf::Text*> c = {&name, &description, &range, &strength, &cooldown};
    for (int i = 0; i < c.size(); i++) {
        auto d = c[i];
        d->setCharacterSize(15);
        d->setPosition(180, 550 + i * 30);
        d->setFont(GetFont());
    }
    auto desc = tow->GetDescription();
    int numberOfNewLines = std::count(desc.begin(), desc.end(), '\n');

    name.setString("Name: " + tow->GetName());
    description.setString(desc);
    description.setPosition(180, 580 + numberOfNewLines * 20);
    range.setString("Range: " + std::to_string(tow->GetRange()));
    range.setPosition(180, 640 + numberOfNewLines * 20);
    strength.setString("Strength: " + std::to_string(tow->GetStrength()));
    strength.setPosition(180, 660 + numberOfNewLines * 20);
    if(tow->GetMainType() == "attack") {
        auto att = (AttackTower*)tow;
        cooldown.setString("Cooldown: " + std::to_string(att->GetCooldownLimit()));
        cooldown.setPosition(180, 680 + numberOfNewLines * 20);
    }


    window_.draw(sprite);
    window_.draw(name);
    for (auto e : c) {
        window_.draw(*e);

    }

}
void GameState::AddPopup(const std::string& content, int posX, bool permanent) {
    auto text = new sf::Text();
    text->setString(content);
    text->setFont(GetFont());
    text->setCharacterSize(20);
    text->setOutlineColor(Color::Black);
    text->setOutlineThickness(3);
    text->setPosition(posX, 40);

    RemovePopup();

    popup_text_.text = text;
    popup_text_.permanent = permanent;
    popup_text_.opacity = 1;
}
void GameState::RemovePopup() {
    delete popup_text_.text;
    popup_text_.text = nullptr;
    popup_text_.permanent = false;
    popup_text_.opacity = 1;
}

void GameState::DrawPopupText() {
    if (popup_text_.text == nullptr) return;
    if (!popup_text_.permanent) { popup_text_.opacity -= 0.005;}
    if (popup_text_.opacity <= 0) {
        RemovePopup();
        return;
    }
    popup_text_.text->setFillColor(Color(255, 255, 255, popup_text_.opacity * 255));
    popup_text_.text->setOutlineColor(Color(0, 0, 0, popup_text_.opacity * 255));
    window_.draw(*popup_text_.text);


}


