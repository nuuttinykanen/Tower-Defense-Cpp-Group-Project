
class Enemy {
    public:
    Enemy(int health, int attack, int bounty) : 
    maxHealth(health), currentHealth(health), attack_(attack), currentBounty(bounty) {}

    ~Enemy(){}

    int getMaxHealth() = { return maxHealth; }
    int getHealth()    = { return currentHealth; }
    int getAttack() = { return attack_; }
    int getBounty() = { return currentBounty; }

    double healthPercentage() = { return (double)currentHealth / (double)maxHealth; }


    void changeHealth(int amount) = { currentHealth += amount; }


    private:

    int maxHealth;
    int currentHealth;
    int currentBounty;
    int attack_;

};

class Zombie : public Enemy {
    public:
    Zombie(int health = 4, int attack = 1, int bounty = 19) : 
    Enemy(health, attack, bounty) {}
    ~Zombie(){}
};

class ZombieHorde : public Enemy {
    public:
    ZombieHorde(int health = 8, int attack = 2, int bounty = 40) : 
    Enemy(health, attack, bounty) {}
    ~ZombieHorde(){}
};

class MichaelMyers : public Enemy {
    public:
    MichaelMyers(int health = 80, int attack = 5, int bounty = 100) : 
    Enemy(health, attack, bounty) {}
    ~MichaelMyers(){}
};

class Dracula : public Enemy {
    public:
    Dracula(int health = 150, int attack = 8, int bounty = 400) : 
    Enemy(health, attack, bounty) {}
    ~Dracula(){}
};

class Bat : public Enemy {
    public:
    Bat(int health = 4, int attack = 10, int bounty = 1) : 
    Enemy(health, attack, bounty) {}
    ~Bat(){}
};