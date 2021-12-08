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
    std::cout << "UPGRADE NOT FOUND" << std::endl;
    return nullptr;
}

void ClockBlocker::supportEffect(MapSquare* square) {
    if(square == nullptr) return;
    std::string type = square->GetType();
    // onko tower
    if(type == "tower") {
        TowerSquare* sq = (TowerSquare*)square;
        // onko attacktower
        if(sq != nullptr && sq->GetTower()->GetType() == "attack") {
            AttackTower* at = (AttackTower*)(sq->GetTower());
            at->AddCooldownModifier(-1 * this->GetStrength());
        }
    }
}

void LightkeeperMerrin::supportEffect(MapSquare* square) {
    if(square == nullptr) return;
    std::string type = square->GetType();
    // onko tower
    if(type == "tower") {
        TowerSquare* sq = (TowerSquare*)square;
        // onko attacktower
        if(sq != nullptr && sq->GetTower()->GetType() == "attack") {
            AttackTower* at = (AttackTower*)(sq->GetTower());
            at->AddCooldownModifier(-1 * this->GetStrength());
        }
    }
}

void DrFrankenstein::supportEffect(MapSquare* square) {
    if(square == nullptr) return;
    std::string type = square->GetType();
    // onko tower
    if(type == "tower") {
        TowerSquare* sq = (TowerSquare*)square;
        // onko attacktower
        if(sq != nullptr && sq->GetTower()->GetType() == "attack") {
            AttackTower* at = (AttackTower*)(sq->GetTower());
            at->AddRangeModifier(this->GetStrength());
        }
    }
}

void MadDrFrankenstein::supportEffect(MapSquare* square) {
    if(square == nullptr) return;
    std::string type = square->GetType();
    // onko tower
    if(type == "tower") {
        TowerSquare* sq = (TowerSquare*)square;
        // onko attacktower
        if(sq != nullptr && sq->GetTower()->GetType() == "attack") {
            AttackTower* at = (AttackTower*)(sq->GetTower());
            at->AddRangeModifier(this->GetStrength());
        }
    }
}

void InsaneDrFrankenstein::supportEffect(MapSquare* square) {
    if(square == nullptr) return;
    std::string type = square->GetType();
    // onko tower
    if(type == "tower") {
        TowerSquare* sq = (TowerSquare*)square;
        // onko attacktower
        if(sq != nullptr && sq->GetTower()->GetType() == "attack") {
            AttackTower* at = (AttackTower*)(sq->GetTower());
            at->AddRangeModifier(this->GetStrength());
        }
    }
}


