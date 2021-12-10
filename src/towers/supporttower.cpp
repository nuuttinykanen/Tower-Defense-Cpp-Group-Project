#include "supporttower.hpp"

std::string SupportTower::GetMainType() const { return "support"; }

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
        if(ts->GetTower()->GetMainType() == "attack") {
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
        if(ts->GetTower()->GetMainType() == "attack") {
            auto tow = (AttackTower*)ts->GetTower();
            tow->AddRangeModifier(this->GetStrength());
        }
    }
}

Tower* MotherBrain::Upgrade() {
    return nullptr;
}

void StereoDude::supportEffect(MapSquare *square) {
    if(square == nullptr) return;
    std::string type = square->GetType();
    if(type == "tower") {
        auto ts = (TowerSquare*)square;
        if(ts->GetTower()->GetMainType() == "attack") {
            auto tow = (AttackTower*)ts->GetTower();
            tow->AddCooldownModifier((int)this->GetStrength() * -1 * 0.01 * tow->GetCooldownLimit());
        }
    }
}

Tower *StereoDude::Upgrade() {
    auto upgrade = new DJDude();
    return upgrade;
}

void DJDude::supportEffect(MapSquare *square) {
    if(square == nullptr) return;
    std::string type = square->GetType();
    if(type == "tower") {
        auto ts = (TowerSquare*)square;
        if(ts->GetTower()->GetMainType() == "attack") {
            auto tow = (AttackTower*)ts->GetTower();
            tow->AddCooldownModifier((int)this->GetStrength() * -1 * 0.01 * tow->GetCooldownLimit());
        }
    }
}

Tower *DJDude::Upgrade() {
    return nullptr;
}


