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

void Player::RemoveTower(Tower *tower) {

    this->playerTowers_.erase(std::remove(this->playerTowers_.begin(), this->playerTowers_.end(), tower), this->playerTowers_.end());

}

void Player::SellTower(Tower *tower) {
    this->GiveMoney(0.5 * tower->GetPrice());
    this->RemoveTower(tower);


}

