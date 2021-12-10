#include "player.hpp"

Player::~Player() {
    for(auto t : playerTowers_) {
        delete (t);
    }
    playerTowers_.clear();
}

std::vector<Tower *> Player::GetTowers() const{
    return playerTowers_;
}

int Player::GetMoney() const{
    return money_;
}

void Player::GiveMoney(int amount) {
    this->money_ += amount;
}

void Player::TakeMoney(int amount) {
    this->money_ -= amount;
}

void Player::RemoveTower(Tower *tower) {

    for (auto t = playerTowers_.begin(); t != playerTowers_.end(); t++) {
        if (*t == tower)
            playerTowers_.erase(t);
    }
}

void Player::SellTower(Tower *tower) {
    this->GiveMoney(0.5 * tower->GetPrice());
    this->RemoveTower(tower);
}

void Player::AddTower(Tower *tower) {
    this->TakeMoney(tower->GetPrice());
    this->playerTowers_.push_back(tower);
}

unsigned int Player::GetMaxHealth() {
    return maxHealth_;
}

unsigned int Player::GetHealth() {
    return health_;
}

void Player::ChangeHealth(int amount) {
    this->health_ += amount;
}

void Player::SetHealth(int amount) {
    health_ = amount;
}

void Player::SetMoney(int amount) {
    money_ = amount;
}