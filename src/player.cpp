#include "player.hpp"


std::vector<Tower *> Player::GetTowers() const{
    return playerTowers_;
}

double Player::GetMoney() const{
    return money_;
}