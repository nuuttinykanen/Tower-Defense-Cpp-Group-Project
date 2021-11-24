#include "enemy.hpp"
#include <string>

    std::string Enemy::GetName() { return name_; }

    int Enemy::GetMaxHealth() { return maxHealth_; }

    int Enemy::GetHealth() { return currentHealth_; }

    int Enemy::GetAttack() { return attack_; }
    
    int Enemy::GetSpeed() { return speed_; }

    int Enemy::GetBounty() { return currentBounty_; }

    bool Enemy::OnMap() { return on_map_; }

    void Enemy::SetOnMap() { on_map_ = true; }

    void Enemy::RemoveFromMap() { on_map_ = false; }

    double Enemy::HealthPercentage() { return (double)currentHealth_ / (double)maxHealth_; }

    void Enemy::ChangeHealth(int amount) { 
        if(currentHealth_ + amount < 0) currentHealth_ = 0;
        else currentHealth_ += amount; 
    }