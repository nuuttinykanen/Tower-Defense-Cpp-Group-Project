#ifndef Enemy_Class
#define Enemy_Class
#include <string>

class Enemy {
    public:
    Enemy(std::string name, int health, int attack, int speed, int bounty) :
    name_(name), maxHealth_(health), currentHealth_(health), attack_(attack), speed_(speed), currentBounty_(bounty) {
        on_map_ = false;
        cooldown_ = speed;
        cooldownModifier_ = 0;
    }

    virtual ~Enemy()= default;

    std::string GetName();
    int GetMaxHealth();
    int GetHealth();
    int GetAttack();
    int GetBounty();
    int GetSpeed();

    bool OnMap();
    void SetOnMap();
    void RemoveFromMap();
    unsigned int GetCooldown();
    void ChangeCooldown(int amount);
    void ResetCooldownModifier();
    void ResetCooldown();
    void SetCooldownModifier();
    unsigned int GetCooldownModifier();
    void ProgressCooldown();

    void ChangeHealth(int amount);
    virtual Enemy* Inner() = 0;
    virtual bool HasInner() = 0;

    private:
    std::string name_;
    int maxHealth_;
    int currentHealth_;
    int attack_;
    int speed_;
    unsigned int cooldown_;
    bool cooldownModifier_;
    int currentBounty_;
    bool on_map_;
};

class Zombie : public Enemy {
    public:
    explicit Zombie(int health = 6, int attack = 3, int speed = 2, int bounty = 20) :
    Enemy("Zombie", health, attack, speed, bounty) {}
    ~Zombie() override= default;
    Enemy* Inner() override;
    bool HasInner() override;
};

class ZombieHorde : public Enemy {
    public:
    explicit ZombieHorde(int health = 16, int attack = 6, int speed = 3, int bounty = 40) :
    Enemy("Zombie Horde", health, attack, speed, bounty) {}
    ~ZombieHorde() override= default;
    Enemy* Inner() override;
    bool HasInner() override;
};

class MichaelMyers : public Enemy {
    public:
    explicit MichaelMyers(int health = 80, int attack = 30, int speed = 4, int bounty = 200) :
    Enemy("Michael Myers", health, attack, speed, bounty) {}
    ~MichaelMyers() override{}
    Enemy* Inner() override;
    bool HasInner() override;
};

class Dracula : public Enemy {
    public:
    explicit Dracula(int health = 150, int attack = 32, int speed = 5, int bounty = 400) :
    Enemy("Dracula", health, attack, speed, bounty) {}
    ~Dracula() override= default;
    Enemy* Inner() override;
    bool HasInner() override;
};

class Bat : public Enemy {
    public:
    explicit Bat(int health = 4, int attack = 20, int speed = 1, int bounty = 10) :
    Enemy("Bat", health, attack, speed, bounty) {}
    ~Bat() override= default;
    Enemy* Inner() override;
    bool HasInner() override;
};

#endif