#include "attacktower.hpp"

    unsigned int AttackTower::currentCooldown() const {
     if(cooldown_ + cooldownModifiers_ > 0) {
         return cooldown_ + cooldownModifiers_;
     }
     return 0;
    }

    double AttackTower::cooldownPercentage() const {
      if(currentCooldown() > 0) {
          return (double)attackCounter_ / (double)currentCooldown();
      }
      return 0;
    }

    bool AttackTower::canAttack() const {
        return attackCounter_ == 0;
    }

    void AttackTower::restartCooldown() {
        attackCounter_ = currentCooldown();
    }

    void AttackTower::reload() {
        if(attackCounter_ > 0) attackCounter_ -= 1;
    }

    unsigned int AttackTower::getRange() const {
        return this->GetRange() + rangeModifiers_;
    }

    void AttackTower::addCooldownModifier(int amount) {
        cooldownModifiers_ += amount;
    }

    void AttackTower::addRangeModifier(int amount) {
        rangeModifiers_ += amount;
    }

    void AttackTower::removeModifiers() {
        cooldownModifiers_ = 0;
        rangeModifiers_ = 0;
    }

    unsigned int AttackTower::currentRange() const {
        return this->GetRange() + rangeModifiers_;
    }