#include "Game.hpp"
#include <cmath>
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
            break;
        }
    }
    this->player_.GiveMoney(enemy->GetBounty());
}

//Deals enemy attack's worth of damage to player
void Game::TakeDamage(Enemy *enemy){
    this->player_.ChangeHealth(-enemy->GetAttack());
    for(auto it = enemies_.begin(); it != enemies_.end(); it++){
        if(*it == enemy){
            if(enemies_.size()==1){
                enemies_.pop_back();
                it--;
            }
            else{
                enemies_.erase(it);
                it--;
            }
        }
    }
}

void Game::SellTower(TowerSquare* towerSquare) {
    this->player_.SellTower(towerSquare->GetTower());
    this->map_.EraseTowerAt(towerSquare);
}



// Start the first wave
void Game::StartWave() {

    startOfWaveHealth_ = player_.GetHealth();
    startOfWaveMoney_ = player_.GetMoney();

    // Not removing the wave since it's simpler to keep track this way
    if(!this->waveInProgress_){
        this->waveInProgress_ = true;
        auto wave = enemyWaves_[this->waveNum_ - 1];
        auto enemyWave = wave->getWaveEnemies();
        this->enemies_ = wave->getWaveEnemies();
    }
}

void Game::EndWave() {

    startOfWaveHealth_ = player_.GetHealth();
    startOfWaveMoney_ = player_.GetMoney();
    this->enemies_.clear();
    if(this->waveInProgress_) {
        this->waveInProgress_ = false;
        this->waveNum_ += 1;
        this->waveSpawned_= false;
        if(waveNum_ > this->GetTotalWaveCount()) {
            this->EndGame();
        }
    }
}

Wave* Game::GetCurrentWave() {
    return this->enemyWaves_[this->waveNum_ - 1];
}


bool Game::isWaveInProgress() {
    return this->waveInProgress_;
}

void Game::EndGame() {
    this->gameEnd_ = true;
}

LevelMap &Game::GetMap() {
    return map_;
}

void Game::ProcessEnemies() {
    //std::cout << "es on map: " << this->map_.GetEnemyAmount() << std::endl;
    if(this->enemyMoveCounter_ < 1) {
        this->map_.MoveEnemies();

        // Place next enemy
        if(this->GetCurrentWave() != nullptr && map_.GetStartSquare() != nullptr && !this->GetCurrentWave()->isEmpty()) {
            auto start_sq = map_.GetStartSquare();
            Enemy& e = this->GetCurrentWave()->PopNext();
            //As the waves recycle the same enemy objects, when starting a second wave
            //the enemies have zero health from the first wave, thus dying at spawn
            //This changes the spawned enemys health to max, if its health = 0
            if(e.GetHealth() < 1){
                e.ChangeHealth(e.GetMaxHealth());
            }
            this->map_.PlaceEnemy(start_sq->GetX(), start_sq->GetY(), e);
            if(this->map_.GetEnemyAmount() == this->enemies_.size()){
                this->waveSpawned_= true;
            }

        }

        this->enemyMoveCounter_ = enemyMoveLimit_;
    }
    this->enemyMoveCounter_ -= 1;

    //Removes killed and passed enemies locally, gives corresponding bounty
    // or damage to player
    for(auto e: this->enemies_){
        if(e->GetHealth() <= 0){
            this->KillEnemy(e);
        }
        else if(e->GetHealth() > 0 and !e->OnMap() and this->map_.GetEnemiesPassed() > 0 && this->waveSpawned_){
            this->TakeDamage(e);
        }
    }
}

void Game::ProcessAttackTowers() {
    for(auto it : this->map_.GetAttackTowers()) {
        auto att = (AttackTower*)it->GetTower();
        if(att->CanAttack()) {
            this->map_.ShootProjectile(it);
        } else {
            att->Reload();
        }
        att->ResetModifiers();
    }
    for(auto ot : this->map_.GetSupportTowers()) {
        auto supp = (SupportTower*)ot->GetTower();
        for(auto it : map_.GetSquares()) {
            double tx = ot->GetX();
            double ty = ot->GetY();
            double x = it.first.first;
            double y = it.first.second;
            if(sqrt(pow(tx - x, 2.0) + pow(ty - y, 2.0)) <= supp->GetRange()) {
                supp->supportEffect(it.second);
            }
        }
    }
}

void Game::UpdateState() {
    if(!this->gameEnd_) {
        if(this->GetCurrentWave()->isEmpty() && map_.GetEnemyAmount() < 1) {
            EndWave();
            return;
        }

        if(this->waveInProgress_) {
            this->ProcessAttackTowers();
            this->ProcessEnemies();
            if(this->player_.GetHealth() < 1) {
                this->EndGame();
            }

            if(projectileMoveCounter_ < 1) {
                this->map_.MoveProjectiles();
                projectileMoveCounter_ = projectileMoveLimit_;
            }
            else projectileMoveCounter_ -= 1;
            // Attack towers shoot or reload

        }
    }
}

void Game::SetWaveNumber(unsigned int newWaveNumber) {
    waveNum_ = newWaveNumber;
}





