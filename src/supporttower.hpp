#ifndef SUPPORTTOWER_HPP
#define SUPPORTTOWER_HPP
#include "tower.hpp"
#include <string>
#include "mapsquare.hpp"
#include "attacktower.hpp"
class SupportTower : public Tower {
    public:
    SupportTower(std::string name, std::string description, int strength, int range, int cost):
     Tower(name, description, strength, range, cost) {}
    ~SupportTower(){}

    virtual void supportEffect(MapSquare* square) = 0;

    virtual std::string GetType() const;

    virtual unsigned int GetRange() const;

};

class Clocker : public SupportTower {
    public:
    Clocker() : SupportTower("Clocker", "Slows down enemies in its range.", 150, 2, 1000) {}
    ~Clocker();

    virtual void supportEffect(MapSquare* square);
    virtual Tower* Upgrade();
};

class ClockBlocker : public SupportTower {
    public:
    ClockBlocker() : SupportTower("Clock Blocker", "Slows down enemies in its range.", 200, 3, 1200) {}
    ~ClockBlocker();
    virtual Tower* Upgrade();

    virtual void supportEffect(MapSquare* square);
};

class Seer : public SupportTower {
    public:
    Seer() : SupportTower("Seer", "Increases range of attack towers within range.", 1, 1, 1200) {}
    ~Seer();
    virtual Tower* Upgrade();

    virtual void supportEffect(MapSquare* square);
};

class MotherBrain : public SupportTower {
public:
    MotherBrain() : SupportTower("Mother Brain", "Increases range of attack towers within range by strength.", 1, 2, 1200) {}
    ~MotherBrain();
    virtual Tower* Upgrade();

    virtual void supportEffect(MapSquare* square);
};

class StereoDude : public SupportTower {
    public:
    StereoDude() : SupportTower("Stereo Dude", "Increases attack rate of attack towers within range by strength.", 1, 2, 1200) {}
    ~StereoDude();
    virtual Tower* Upgrade();

    virtual void supportEffect(MapSquare* square);
};

class DJDude : public SupportTower {
public:
    DJDude() : SupportTower("DJ Dude", "Increases attack rate of attack towers within range by strength.", 2, 3, 1200) {}
    ~DJDude();
    virtual Tower* Upgrade();

    virtual void supportEffect(MapSquare* square);
};

#endif