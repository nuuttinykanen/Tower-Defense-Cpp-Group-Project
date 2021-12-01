#include "../Gui.h"
#include "game_state.h"
#include "menu_state.h"

GameState::GameState(sf::RenderWindow &window, Gui* gui) : WindowState(window, gui) {
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

    auto wave = new Wave({new Zombie(), new ZombieHorde(), new Zombie()});



    std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> coords = std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>>();
    std::pair<int, int> start = std::make_pair(2, 4);
    std::pair<int, int> middle = std::make_pair(2, 9);
    std::pair<int, int> end1 = std::make_pair(10, 9);
    std::pair<int, int> end2 = std::make_pair(10, 14);
    std::pair<int, int> end3 = std::make_pair(15, 14);
    coords.emplace_back(start, middle);
    coords.emplace_back(middle, end1);
    coords.emplace_back(end1, end2);
    coords.emplace_back(end2, end3);
    levelMap_ = new LevelMap(100);
    levelMap_->InitializePath(coords);
    auto p = Player();
    game_ = new Game( *levelMap_, p, {wave});
}
GameState::~GameState() {
    for (auto b : buttons_) {
        delete b.second;
    }
}

void GameState::advance_state() {
    game_->UpdateState();
}

void GameState::draw_current_state() {
    for (auto b : buttons_) {
        b.second->draw(window_);
    }
    auto globals = gui_->getGlobalObjects();

    auto purpleSprite = globals->getPurpleEnemySprite();
    purpleSprite.setScale(2, 2);
    purpleSprite.setPosition(500, 500);
    window_.draw(purpleSprite);
    LevelMap& map = game_->GetMap();
    for(auto it : map.GetFreeSquares()) {
        auto freeSprite = globals->getFreeSquareSprite();
        freeSprite.setPosition(it.second->GetX(), it.second->GetY());
        window_.draw(freeSprite);
    }
    for(auto it : map.GetEnemySquares()) {
        auto freeSprite = globals->getEnemySquareSprite();
        freeSprite.setPosition(it.second->GetX(), it.second->GetY());
        window_.draw(freeSprite);
    }
    for(auto it : map.GetTowerSquares()) {
        auto freeSprite = globals->getTowerSquareSprite();
        freeSprite.setPosition(it.second->GetX(), it.second->GetY());
        window_.draw(freeSprite);
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
            } else if (event.mouseButton.button == 1) {

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
    if (game_->GetWaveCount() == 0) {
        // Remove the start wave button
        for (auto it = buttons_.begin(); it != buttons_.end(); it++) {
            if (it->first == GameButtonTarget::StartWave) {
                delete it->second;
                buttons_.erase(it);
            }
        }
    }
}
