#include "player.hpp"


std::vector<Tower *> Player::GetTowers() const{
    return playerTowers_;
}

double Player::GetMoney() const{
    return money_;
}

void Player::GiveMoney(double amount) {
    this->money_ += amount;
}

void Player::TakeMoney(double amount) {
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

void Player::BuyTower(Tower *tower) {
    this->TakeMoney(tower->GetPrice());
    this->playerTowers_.push_back(tower);
}

