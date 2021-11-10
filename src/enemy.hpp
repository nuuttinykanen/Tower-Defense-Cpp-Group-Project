#ifndef Enemy_Class
#define Enemy_Class

class Enemy {
    public:
    Enemy(std::string name, int health, int attack, int bounty) : 
    name_(name), maxHealth_(health), currentHealth_(health), attack_(attack), currentBounty_(bounty) {}

    ~Enemy(){}
    std::string GetName() { return name_; }
    int getMaxHealth() { return maxHealth_; }
    int getHealth() { return currentHealth_; }
    int getAttack() { return attack_; }
    int getBounty() { return currentBounty_; }

    double healthPercentage() { return (double)currentHealth_ / (double)maxHealth_; }


    void changeHealth(int amount) { currentHealth_ += amount; }


    private:
    std::string name_;
    int maxHealth_;
    int currentHealth_;
    int currentBounty_;
    int attack_;

};

class Zombie : public Enemy {
    public:
    Zombie(int health = 4, int attack = 1, int bounty = 19) : 
    Enemy("Zombie", health, attack, bounty) {}
    ~Zombie(){}
};

class ZombieHorde : public Enemy {
    public:
    ZombieHorde(int health = 8, int attack = 2, int bounty = 40) : 
    Enemy("Zombie Horde", health, attack, bounty) {}
    ~ZombieHorde(){}
};

class MichaelMyers : public Enemy {
    public:
    MichaelMyers(int health = 80, int attack = 5, int bounty = 100) : 
    Enemy("Michael Myers", health, attack, bounty) {}
    ~MichaelMyers(){}
};

class Dracula : public Enemy {
    public:
    Dracula(int health = 150, int attack = 8, int bounty = 400) : 
    Enemy("Dracula", health, attack, bounty) {}
    ~Dracula(){}
};

class Bat : public Enemy {
    public:
    Bat(int health = 4, int attack = 10, int bounty = 1) : 
    Enemy("Bat", health, attack, bounty) {}
    ~Bat(){}
};

#endif