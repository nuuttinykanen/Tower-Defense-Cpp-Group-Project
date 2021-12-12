#include "player.hpp"

Player::~Player() = default;


int Player::GetMoney() const{
    return money_;
}

void Player::GiveMoney(int amount) {
    this->money_ += amount;
}

void Player::TakeMoney(int amount) {
    this->money_ -= amount;
}

void Player::SellTower(Tower *tower) {
    this->GiveMoney(0.5 * tower->GetPrice());
}

void Player::AddTower(Tower *tower) {
    this->TakeMoney(tower->GetPrice());
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