#include "enemy.hpp"
#include <string>

    std::string Enemy::GetName() { return name_; }

    int Enemy::GetMaxHealth() { return maxHealth_; }

    int Enemy::GetHealth() { return currentHealth_; }

    int Enemy::GetAttack() { return attack_; }
    
    int Enemy::GetSpeed() { return speed_; }

    int Enemy::GetBounty() { return currentBounty_; }

    double Enemy::HealthPercentage() { return (double)currentHealth_ / (double)maxHealth_; }

    void Enemy::ChangeHealth(int amount) { currentHealth_ += amount; }