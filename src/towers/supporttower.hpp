#ifndef SUPPORTTOWER_HPP
#define SUPPORTTOWER_HPP
#include "tower.hpp"
#include <string>
#include "../mapsquare.hpp"
#include "attacktower.hpp"
class SupportTower : public Tower {
    public:
    SupportTower(std::string name, std::string description, int strength, int range, int cost):
     Tower(name, description, strength, range, cost) {}
    ~SupportTower() override = default;

    virtual void supportEffect(MapSquare* square) = 0;

    [[nodiscard]] std::string GetMainType() const override;

    [[nodiscard]] unsigned int GetRange() const override;

};

class Clocker : public SupportTower {
    public:
    Clocker() : SupportTower("Clocker", "Slows down enemies in its range \nby 'STRENGTH' percent.\nDoes not stack.", 40, 2, 350) {}
    ~Clocker() override = default;;

    void supportEffect(MapSquare* square) override;

    [[nodiscard]] TowerTypes getType() const override {return TowerTypes::ClockerType;}

    Tower* Upgrade() override;
};

class ClockBlocker : public SupportTower {
    public:
    ClockBlocker() : SupportTower("Clock Blocker", "Slows down enemies in its range \nby 'STRENGTH' percent.\nDoes not stack.", 60, 3, 450) {}
    ~ClockBlocker() override = default;;
    Tower* Upgrade() override;

    bool CanUpgrade() override {return false;}

    [[nodiscard]] TowerTypes getType() const override {return TowerTypes::ClockerBlockerType;}

    void supportEffect(MapSquare* square) override;
};

class Seer : public SupportTower {
    public:
    Seer() : SupportTower("Seer", "Increases range of attack towers \nwithin range by 'STRENGTH'. \nDoes not stack.", 1, 1, 450) {}
    ~Seer() override = default;;
    Tower* Upgrade() override;

    [[nodiscard]] TowerTypes getType() const override {return TowerTypes::SeerType;}

    void supportEffect(MapSquare* square) override;
};

class MotherBrain : public SupportTower {
public:
    MotherBrain() : SupportTower("Mother Brain", "Increases range of attack towers \nwithin range by 'STRENGTH'. \nDoes not stack.", 1, 2, 500) {}
    ~MotherBrain() override = default;;

    bool CanUpgrade() override {return false;}

    Tower* Upgrade() override;

    [[nodiscard]] TowerTypes getType() const override {return TowerTypes::MotherBrainType;}


    void supportEffect(MapSquare* square) override;
};

class StereoDude : public SupportTower {
    public:
    StereoDude() : SupportTower("Stereo Dude", "Increases attack rate of attack \ntowers within range by 'STRENGTH'. \nDoes not stack.", 30, 1, 400) {}
    ~StereoDude() override = default;;
    Tower* Upgrade() override;

    [[nodiscard]] TowerTypes getType() const override {return TowerTypes::StereoType;}

    void supportEffect(MapSquare* square) override;
};

class DJDude : public SupportTower {
public:
    DJDude() : SupportTower("DJ Dude", "Increases attack rate of attack \ntowers within range by 'STRENGTH'. \nDoes not stack.", 50, 2, 500) { }
    ~DJDude() override = default;;

    [[nodiscard]] TowerTypes getType() const override {return TowerTypes::DJDudeType;}

    bool CanUpgrade() override {return false;}

    Tower* Upgrade() override;

    void supportEffect(MapSquare* square) override;
};

#endif