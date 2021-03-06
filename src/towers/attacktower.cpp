#include "attacktower.hpp"

int AttackTower::CurrentCooldown() const {
 if(cooldown_ > 0) {
     return cooldown_;
 }
 else return 0;
}

bool AttackTower::CanAttack() const {
    return this->CurrentCooldown() <= 0;
}

void AttackTower::RestartCooldown() {
    cooldown_ = this->GetCooldownLimit();
    cooldownModifiers_ = 0;
}

void AttackTower::Reload() {
    if(cooldown_ > 0) cooldown_ -= 1;
}

unsigned int AttackTower::GetRange() const {
    return this->range_ + rangeModifiers_;
}

void AttackTower::AddCooldownModifier(int amount) {
    if(amount < cooldownModifiers_) cooldownModifiers_ += amount;
}

void AttackTower::AddRangeModifier(int amount) {
    rangeModifiers_ += amount;
}

void AttackTower::ResetModifiers() {
    cooldownModifiers_ = 0;
    rangeModifiers_ = 0;
}

std::string AttackTower::GetMainType() const { return "attack"; }

int AttackTower::GetCooldownLimit() const {
    return cooldownLimit_ + cooldownModifiers_;
}

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

Projectile *CursedKid::GetProjectile() {
    Projectile* projec = new CursedProjectile(this, 2);
    return projec;
}

Tower *CursedKid::Upgrade() {
    auto upgrade = new MaskedKid();
    return upgrade;
}

Projectile *MaskedKid::GetProjectile() {
    Projectile* projec = new CursedProjectile(this, 3);
    return projec;
}

Tower *MaskedKid::Upgrade() {
    auto upgrade = new MaskedGod();
    return upgrade;
}

Projectile *MaskedGod::GetProjectile() {
    Projectile* projec = new CursedProjectile(this, 5);
    return projec;
}

Tower *MaskedGod::Upgrade() {
    return nullptr;
}
Projectile* KnifeBot::GetProjectile() {
    Projectile* projec = new BulletProjectile(this);
    return projec;
}

Tower* KnifeBot::Upgrade() {
    auto upgrade = new KnifeBot2();
    return upgrade;
}

Projectile* KnifeBot2::GetProjectile() {
    Projectile* projec = new BulletProjectile(this);
    return projec;
}

Tower* KnifeBot2::Upgrade() {
    auto upgrade = new SwordBot();
    return upgrade;
}

Projectile* SwordBot::GetProjectile() {
    Projectile* projec = new BulletProjectile(this);
    return projec;
}

Tower* SwordBot::Upgrade() {
    return nullptr;
}
