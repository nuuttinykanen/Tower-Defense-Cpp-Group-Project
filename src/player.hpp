
#include "tower.hpp"

#ifndef TOWER_DEFENSE_12_PLAYER_HPP
#define TOWER_DEFENSE_12_PLAYER_HPP


class Player {

    public :
        Player(int money = 100, std::vector<Tower*> towers = std::vector<Tower*>() ) : money_(money), playerTowers_(towers) {}

        std::vector<Tower*> GetTowers() const;
        double GetMoney() const;


    private :
        double money_;
        std::vector<Tower*> playerTowers_;
};


#endif //TOWER_DEFENSE_12_PLAYER_HPP
