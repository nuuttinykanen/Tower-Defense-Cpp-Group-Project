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
        return attackCounter_ <= 0;
    }

    void AttackTower::RestartCooldown() {
        attackCounter_ = CurrentCooldown();
    }

    void AttackTower::Reload() {
        if(attackCounter_ > 0) attackCounter_ -= 1;
    }

    unsigned int AttackTower::GetRange() const {
        return this->range_ + rangeModifiers_;
    }

    void AttackTower::AddCooldownModifier(int amount) {
        cooldownModifiers_ += amount;
    }

    void AttackTower::AddRangeModifier(int amount) {
        rangeModifiers_ += amount;
    }

    void AttackTower::ResetModifiers() {
        cooldownModifiers_ = 0;
        rangeModifiers_ = 0;
    }

    std::string AttackTower::GetMainType() const { return "attack"; }

    Projectile* Bomber::GetProjectile() {
        Projectile* projec = new BombProjectile(this);
        return projec;
    }

    Tower* Bomber::Upgrade() {
        auto upgrade = new SuperBomber();
        return upgrade;
    }

    Projectile* SuperBomber::GetProjectile() {
        Projectile* projec = new BombProjectile(this);
        return projec;
    }

    Tower* SuperBomber::Upgrade() {
        auto upgrade = new UltraBomber();
        return upgrade;
    }

    Projectile* UltraBomber::GetProjectile() {
        Projectile* projec = new BombProjectile(this);
        return projec;
    }

    Tower* UltraBomber::Upgrade() {
        return nullptr;
    }


    Projectile* Gunner::GetProjectile() {
        Projectile* projec = new BulletProjectile(this);
        return projec;
    }

    Tower* Gunner::Upgrade() {
        auto upgrade = new Multigunner();
        return upgrade;
    }

    Projectile* Multigunner::GetProjectile() {
        Projectile* projec = new BulletProjectile(this);
        return projec;
    }

    Tower* Multigunner::Upgrade() {
        auto upgrade = new GunFiend();
        return upgrade;
    }

    Projectile* GunFiend::GetProjectile() {
        Projectile* projec = new BulletProjectile(this);
        return projec;
    }

    Tower* GunFiend::Upgrade() {
        return nullptr;
    }

