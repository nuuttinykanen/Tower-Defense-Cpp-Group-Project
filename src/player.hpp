
#include "tower.hpp"

#ifndef TOWER_DEFENSE_12_PLAYER_HPP
#define TOWER_DEFENSE_12_PLAYER_HPP


class Player {

    public :
        Player(unsigned int maxHealth, int money = 500, std::vector<Tower*> towers = std::vector<Tower*>() ) : maxHealth_(maxHealth), money_(money), playerTowers_(towers) {
            health_ = maxHealth;
        }
        ~Player();

        std::vector<Tower*> GetTowers() const;

        int GetMoney() const;
        void SetMoney(int amount);
        void GiveMoney(int amount);
        void TakeMoney(int amount);
        void RemoveTower(Tower* tower);
        void SellTower(Tower* tower);
        void AddTower(Tower* tower);

        unsigned int GetMaxHealth();
        unsigned int GetHealth();
        void ChangeHealth(int amount);
        void SetHealth(int amount);


    private:
        unsigned int maxHealth_;
        unsigned int health_;
        int money_;
        std::vector<Tower*> playerTowers_;
};


#endif //TOWER_DEFENSE_12_PLAYER_HPP
