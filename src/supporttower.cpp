#include "supporttower.hpp"

std::string SupportTower::GetType() const { return "support"; }

unsigned int SupportTower::GetRange() const { return this->range_; }

void FatherMerrin::supportEffect(MapSquare* square) {
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

void EnlightenedMerrin::supportEffect(MapSquare* square) {
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


    