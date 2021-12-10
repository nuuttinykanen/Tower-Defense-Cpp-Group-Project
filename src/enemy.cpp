#include "enemy.hpp"
#include <iostream>
    std::string Enemy::GetName() { return name_; }

    int Enemy::GetMaxHealth() { return maxHealth_; }

    int Enemy::GetHealth() { return currentHealth_; }

    int Enemy::GetAttack() { return attack_; }
    
    int Enemy::GetSpeed() { return speed_; }

    int Enemy::GetBounty() { return currentBounty_; }

    bool Enemy::OnMap() { return on_map_; }

    void Enemy::SetOnMap() { on_map_ = true; }

    void Enemy::RemoveFromMap() { on_map_ = false; }

    void Enemy::ChangeHealth(int amount) {
        if (currentHealth_ + amount < 0) currentHealth_ = 0;
        else currentHealth_ += amount;
    }

unsigned int Enemy::GetCooldown() {
    return this->cooldown_;
}

void Enemy::ChangeCooldown(int amount) {
    this->cooldown_ += amount;
}

void Enemy::ResetCooldownModifier() {
    this->cooldownModifier_ = false;
}

void Enemy::ResetCooldown() {
    this->ResetCooldownModifier();
    this->cooldown_ = this->GetSpeed();
}

void Enemy::SetCooldownModifier() {
    this->cooldownModifier_ = true;
}

void Enemy::ProgressCooldown() {
    if(this->cooldown_ > 0) cooldown_ -= 1;
    else this->ResetCooldown();
}

unsigned int Enemy::GetCooldownModifier() {
    return this->cooldownModifier_;
}

Enemy *Zombie::Inner() {
    return nullptr;
}


Enemy *ZombieHorde::Inner() {
    auto inner = new Zombie();
    return inner;
}

Enemy *MichaelMyers::Inner() {
    return nullptr;
}

Enemy *Dracula::Inner() {
    return nullptr;
}

Enemy *Bat::Inner() {
    auto inner = new Dracula();
    return inner;
}
