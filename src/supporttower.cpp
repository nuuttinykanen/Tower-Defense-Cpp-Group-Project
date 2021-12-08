#include "supporttower.hpp"

std::string SupportTower::GetType() const { return "support"; }

unsigned int SupportTower::GetRange() const { return this->range_; }

void Clocker::supportEffect(MapSquare* square) {
    if(square == nullptr) return;
    std::string type = square->GetType();
    // onko tower
    if(type == "enemy") {
        EnemySquare* en = (EnemySquare*)square;
        for(auto it : en->GetEnemies()) {
            if(it->GetCooldownModifier() == false) {
                it->SetCooldownModifier();
                it->ChangeCooldown(this->GetStrength() * it->GetSpeed() * 0.01);
            }
        }
    }
}

Tower* Clocker::Upgrade() {
    auto upgrade = new ClockBlocker();
    return upgrade;
}

void ClockBlocker::supportEffect(MapSquare* square) {
    if(square == nullptr) return;
    std::string type = square->GetType();
    // onko tower
    if(type == "enemy") {
        EnemySquare* en = (EnemySquare*)square;
        for(auto it : en->GetEnemies()) {
            if(it->GetCooldownModifier() == false) {
                it->SetCooldownModifier();
                it->ChangeCooldown(this->GetStrength() * it->GetSpeed() * 0.01);
            }
        }
    }
}

Tower* ClockBlocker::Upgrade() {
    return nullptr;
}

void Seer::supportEffect(MapSquare* square) {
    if(square == nullptr) return;
    std::string type = square->GetType();
    if(type == "tower") {
        auto ts = (TowerSquare*)square;
        if(ts->GetTower()->GetType() == "attack") {
            auto tow = (AttackTower*)ts->GetTower();
            tow->AddRangeModifier(this->GetStrength());
        }
    }
}

Tower* Seer::Upgrade() {
    auto upgrade = new MotherBrain();
    return upgrade;
}

void MotherBrain::supportEffect(MapSquare* square) {
    if(square == nullptr) return;
    std::string type = square->GetType();
    if(type == "tower") {
        auto ts = (TowerSquare*)square;
        if(ts->GetTower()->GetType() == "attack") {
            auto tow = (AttackTower*)ts->GetTower();
            tow->AddRangeModifier(tow->GetRange() * 0.01 * this->GetStrength());
        }
    }
}

Tower* MotherBrain::Upgrade() {
    return nullptr;
}




