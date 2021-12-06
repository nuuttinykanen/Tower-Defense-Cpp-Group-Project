#ifndef SUPPORTTOWER_HPP
#define SUPPORTTOWER_HPP
#include "tower.hpp"
#include <string>
#include "mapsquare.hpp"
#include "attacktower.hpp"
class SupportTower : public Tower {
    public:
    SupportTower(std::string name, std::string description, int strength, int range, int cost, std::string upgrade):
     Tower(name, description, strength, range, cost, upgrade) {}
    ~SupportTower(){}

    virtual void supportEffect() = 0;

    virtual std::string GetType() const;

    virtual unsigned int GetRange() const;

};

class FatherMerrin : public SupportTower {
    public:
    FatherMerrin() : SupportTower("Father Merrin", "Reduces the countdown of every recruit in its range by strength.", 1, 1, 1000, "") {}
    ~FatherMerrin();

    virtual void supportEffect(MapSquare* square);
};

class EnlightenedMerrin : public SupportTower {
    public:
    EnlightenedMerrin() : SupportTower("Enlightened Merrin", "Reduces the countdown of every recruit in its range by strength.", 2, 1, 1200, "") {}
    ~EnlightenedMerrin();

    virtual void supportEffect(MapSquare* square);
};

class LightkeeperMerrin : public SupportTower {
    public:
    LightkeeperMerrin() : SupportTower("Lightkeeper Merrin", "Reduces the countdown of every recruit in its range by strength.", 2, 2, 1400, "") {}
    ~LightkeeperMerrin();

    virtual void supportEffect(MapSquare* square);
};

class DrFrankenstein : public SupportTower {
    public:
    DrFrankenstein() : SupportTower("Dr. Frankenstein", "Extends the range of all attacking recruits within his range by strength.", 1, 1, 1100, "") {}
    ~DrFrankenstein();

    virtual void supportEffect(MapSquare* square);
};

class MadDrFrankenstein : public SupportTower {
    public:
    MadDrFrankenstein() : SupportTower("Mad Frankenstein", "Extends the range of all attacking recruits within his range by strength.", 2, 1, 1100, "") {}
    ~MadDrFrankenstein();

   virtual void supportEffect(MapSquare* square);
};

class InsaneDrFrankenstein : public SupportTower {
    public:
    InsaneDrFrankenstein() : SupportTower("INSANE Dr. Frankenstein", "Extends the range of all attacking recruits within his range by strength.", 1, 1, 1100, "") {}
    ~InsaneDrFrankenstein();

    virtual void supportEffect(MapSquare* square);
};

#endif