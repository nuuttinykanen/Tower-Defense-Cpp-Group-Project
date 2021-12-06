#include "Game.hpp"

Game::~Game(){
    for(auto w : enemyWaves_) {
        delete(w);
    }
    enemyWaves_.clear();

}

void Game::SpawnEnemy(Enemy* enemy) {
    //Enemypath start square (spawn) coordinates
    int x = this->map_.GetEnemySquares().begin()->first.first;
    int y = this-> map_.GetEnemySquares().begin()->first.second;


    if(this->map_.PlaceEnemy(x, y, *enemy)){
        enemies_.push_back(enemy);
    }

}

void Game::SpawnTower(Tower* tower, double x, double y) {
    this->player_.AddTower(tower);
    this->map_.PlaceTower(x, y, tower);
    towers_.push_back(tower);

}

//Kills enemy locally, gives money to player
void Game::KillEnemy(Enemy *enemy) {
    for(std::vector<Enemy*>::iterator it = enemies_.begin(); it != enemies_.end(); it++){
        if(*it == enemy){
            enemies_.erase(it);
        }
    }
    this->player_.GiveMoney(enemy->GetBounty());

}


void Game::SellTower(Tower* tower) {
    this->player_.SellTower(tower);
    this->map_.EraseTower(tower);
}



// Start the first wave and then remove it from the vector
void Game::StartWave() {

    this->waveInProgress_ = true;
    auto wave = enemyWaves_[this->waveNum_ - 1];
    auto enemyWave = wave->getWaveEnemies();
    this->enemies_ = wave->getWaveEnemies();
    enemyWaves_.erase(enemyWaves_.begin());

}
void Game::EndWave() {
    if(this->waveInProgress_) {
        this->waveInProgress_ = false;
        this->waveNum_ += 1;
        if(waveNum_ > this->GetTotalWaveCount()) {
            this->EndGame();
        }
    }
}

Wave* Game::GetCurrentWave() {
    return this->enemyWaves_[this->waveNum_ - 1];
}

unsigned int Game::GetTotalWaveCount() {
    return this->enemyWaves_.size();
}

bool Game::ifWaveInProgress() {
    return this->waveInProgress_;
}

void Game::EndGame() {
    this->gameEnd_ = true;
}

LevelMap &Game::GetMap() {
    return map_;
}

void Game::ProcessEnemies() {

    //Removes killed enemies locally, gives corresponding bounty to player
    for(auto e: this->enemies_){
        if(e->GetHealth() <= 0){
            this->KillEnemy(e);
        }
    }

    if(this->moveCounter_ < 1) {
        this->map_.MoveEnemies();
        // Place next enemy
        if(this->GetCurrentWave() != nullptr && map_.GetStartSquare() != nullptr && !this->GetCurrentWave()->isEmpty()) {
            auto start_sq = map_.GetStartSquare();
            this->map_.PlaceEnemy(start_sq->GetX(), start_sq->GetY(), this->GetCurrentWave()->PopNext());
        }
        this->moveCounter_ = moveLimit_;
    }
    this->moveCounter_ -= 1;
}

void Game::ProcessAttackTowers() {
    for(auto it : this->map_.GetAttackTowers()){
        auto att = (AttackTower*)it->GetTower();
        if(att->CanAttack()) {
            this->map_.ShootProjectile(it);
        } else {
            att->Reload();
        }
    }
}

void Game::UpdateState() {

    std::cout << "Player health: " << this->player_.GetHealth() << std::endl;
    std::cout << "Player money: " << this->player_.GetMoney() << std::endl;


    if(!this->gameEnd_) {
        if(this->GetCurrentWave()->isEmpty() && map_.GetEnemyAmount() < 1) {
            this->waveInProgress_ = false;
            return;
        }
        if(this->waveInProgress_) {
            this->ProcessEnemies();
            if(this->player_.GetHealth() < 1) {
                std::cout << "ENDING GAME" << std::endl;
                this->EndGame();
            }
            //Move Projectiles
            this->map_.MoveProjectiles();
            this->map_.MoveProjectiles();
            // Attack towers shoot or reload
            this->ProcessAttackTowers();
        }
    }
}





