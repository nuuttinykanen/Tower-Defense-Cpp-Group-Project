#ifndef Enemy_Class
#define Enemy_Class

class Enemy {
    public:
    Enemy(std::string name, int health, int attack, int speed, int bounty) : 
    name_(name), maxHealth_(health), currentHealth_(health), attack_(attack), speed_(speed), currentBounty_(bounty) {
        on_map_ = false;
    }

    ~Enemy(){}

    std::string GetName();
    int GetMaxHealth();
    int GetHealth();
    int GetAttack();
    int GetBounty();
    int GetSpeed();

    bool OnMap();
    void SetOnMap();
    void RemoveFromMap();

    double HealthPercentage();

    void ChangeHealth(int amount);

    private:
    std::string name_;
    int maxHealth_;
    int currentHealth_;
    int attack_;
    int speed_;
    int currentBounty_;
    bool on_map_;
};

class Zombie : public Enemy {
    public:
    Zombie(int health = 4, int attack = 1, int speed = 1, int bounty = 19) : 
    Enemy("Zombie", health, attack, speed, bounty) {}
    ~Zombie(){}
};

class ZombieHorde : public Enemy {
    public:
    ZombieHorde(int health = 8, int attack = 2, int speed = 2, int bounty = 40) : 
    Enemy("Zombie Horde", health, attack, speed, bounty) {}
    ~ZombieHorde(){}
};

class MichaelMyers : public Enemy {
    public:
    MichaelMyers(int health = 80, int attack = 5, int speed = 1, int bounty = 100) : 
    Enemy("Michael Myers", health, attack, speed, bounty) {}
    ~MichaelMyers(){}
};

class Dracula : public Enemy {
    public:
    Dracula(int health = 150, int attack = 8, int speed = 1, int bounty = 400) : 
    Enemy("Dracula", health, attack, speed, bounty) {}
    ~Dracula(){}
};

class Bat : public Enemy {
    public:
    Bat(int health = 4, int attack = 10, int speed = 2, int bounty = 1) : 
    Enemy("Bat", health, attack, speed, bounty) {}
    ~Bat(){}
};

#endif