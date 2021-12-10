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

    virtual std::string GetMainType() const;

    virtual unsigned int GetRange() const;

};

class Clocker : public SupportTower {
    public:
    Clocker() : SupportTower("Clocker", "Slows down enemies in its range \nby 'STRENGTH' percent.\nDoes not stack.", 150, 2, 1) {}
    ~Clocker() { };

    virtual void supportEffect(MapSquare* square);

    virtual TowerTypes getType() const {return TowerTypes::ClockerType;}

    virtual Tower* Upgrade();
};

class ClockBlocker : public SupportTower {
    public:
    ClockBlocker() : SupportTower("Clock Blocker", "Slows down enemies in its range \nby 'STRENGTH' percent.\nDoes not stack.", 200, 3, 1) {}
    ~ClockBlocker() { };
    virtual Tower* Upgrade();

    bool CanUpgrade() override {return false;}

    virtual TowerTypes getType() const {return TowerTypes::ClockerBlockerType;}

    virtual void supportEffect(MapSquare* square);
};

class Seer : public SupportTower {
    public:
    Seer() : SupportTower("Seer", "Increases range of attack towers \nwithin range by 'STRENGTH'. Does not stack.", 1, 1, 1) {}
    ~Seer() { };
    virtual Tower* Upgrade();

    virtual TowerTypes getType() const {return TowerTypes::SeerType;}

    virtual void supportEffect(MapSquare* square);
};

class MotherBrain : public SupportTower {
public:
    MotherBrain() : SupportTower("Mother Brain", "Increases range of attack towers \nwithin range by 'STRENGTH'. Does not stack.", 1, 2, 1) {}
    ~MotherBrain() {};

    bool CanUpgrade() override {return false;}

    virtual Tower* Upgrade();

    virtual TowerTypes getType() const {return TowerTypes::MotherBrainType;}


    virtual void supportEffect(MapSquare* square);
};

class StereoDude : public SupportTower {
    public:
    StereoDude() : SupportTower("Stereo Dude", "Increases attack rate of attack towers \nwithin range by 'STRENGTH'. Does not stack.", 30, 4, 1) {}
    ~StereoDude() { };
    virtual Tower* Upgrade();

    virtual TowerTypes getType() const {return TowerTypes::StereoType;}

    virtual void supportEffect(MapSquare* square);
};

class DJDude : public SupportTower {
public:
    DJDude() : SupportTower("DJ Dude", "Increases attack rate of attack towers \nwithin range by strength. Does not stack.", 50, 3, 1) { }
    ~DJDude() { };

    virtual TowerTypes getType() const {return TowerTypes::DJDudeType;}

    bool CanUpgrade() override {return false;}

    virtual Tower* Upgrade();

    virtual void supportEffect(MapSquare* square);
};

#endif