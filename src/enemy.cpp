#include "enemy.hpp"
#include <string>

    std::string Enemy::GetName() { return name_; }

    int Enemy::getMaxHealth() { return maxHealth_; }

    int Enemy::getHealth() { return currentHealth_; }

    int Enemy::getAttack() { return attack_; }
    
    int Enemy::getBounty() { return currentBounty_; }

    double Enemy::healthPercentage() { return (double)currentHealth_ / (double)maxHealth_; }

    void Enemy::changeHealth(int amount) { currentHealth_ += amount; }