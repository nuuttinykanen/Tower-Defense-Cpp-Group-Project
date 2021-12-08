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
    ClockBlocker() : SupportTower("Clock Blocker", "Slows down enemies in its range.", 3, 3, 1200) {}
    ~ClockBlocker();

    virtual void supportEffect(MapSquare* square);
};

class LightkeeperMerrin : public SupportTower {
    public:
    LightkeeperMerrin() : SupportTower("Lightkeeper Merrin", "Reduces the countdown of every recruit in its range by strength.", 2, 2, 1400) {}
    ~LightkeeperMerrin();

    virtual void supportEffect(MapSquare* square);
};

class DrFrankenstein : public SupportTower {
    public:
    DrFrankenstein() : SupportTower("Dr. Frankenstein", "Extends the range of all attacking recruits within his range by strength.", 1, 1, 1100) {}
    ~DrFrankenstein();

    virtual void supportEffect(MapSquare* square);
};

class MadDrFrankenstein : public SupportTower {
    public:
    MadDrFrankenstein() : SupportTower("Mad Frankenstein", "Extends the range of all attacking recruits within his range by strength.", 2, 1, 1100) {}
    ~MadDrFrankenstein();

   virtual void supportEffect(MapSquare* square);
};

class InsaneDrFrankenstein : public SupportTower {
    public:
    InsaneDrFrankenstein() : SupportTower("INSANE Dr. Frankenstein", "Extends the range of all attacking recruits within his range by strength.", 1, 1, 1100) {}
    ~InsaneDrFrankenstein();

    virtual void supportEffect(MapSquare* square);
};

#endif