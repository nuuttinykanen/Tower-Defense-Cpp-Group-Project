#include "attacktower.hpp"

    unsigned int AttackTower::CurrentCooldown() const {
     if(cooldown_ + cooldownModifiers_ > 0) {
         return cooldown_ + cooldownModifiers_;
     }
     return 0;
    }

    double AttackTower::CooldownPercentage() const {
      if(CurrentCooldown() > 0) {
          return (double)attackCounter_ / (double)CurrentCooldown();
      }
      return 0;
    }

    bool AttackTower::CanAttack() const {
        return attackCounter_ == 0;
    }

    void AttackTower::RestartCooldown() {
        attackCounter_ = CurrentCooldown();
    }

    void AttackTower::Reload() {
        if(attackCounter_ > 0) attackCounter_ -= 1;
    }

    unsigned int AttackTower::GetRange() const {
        return this->GetRange() + rangeModifiers_;
    }

    void AttackTower::AddCooldownModifier(int amount) {
        cooldownModifiers_ += amount;
    }

    void AttackTower::AddRangeModifier(int amount) {
        rangeModifiers_ += amount;
    }

    void AttackTower::RemoveModifiers() {
        cooldownModifiers_ = 0;
        rangeModifiers_ = 0;
    }

    unsigned int AttackTower::CurrentRange() const {
        return this->GetRange() + rangeModifiers_;
    }

    std::string AttackTower::GetType() const { return "attack"; }
