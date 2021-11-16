#ifndef LEVELMAP_CPP
#define LEVELMAP_CPP
#include "levelmap.hpp"

void LevelMap::InitializePath(std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> enemy_path) {
    for(auto it : enemy_path) {
      std::pair<int, int> first = it.first;
      std::pair<int, int> second = it.second;
      while(first != second) {
          std::pair<int, int> ins = std::make_pair(first.first, first.second);
          EnemySquare* new_square = new EnemySquare(ins.first, ins.second, std::vector<Enemy*>());
          ChangeSquare(ins.first, ins.second, new_square);
          enemy_path_.insert(std::make_pair(std::make_pair(ins.first, ins.second), new_square));

          // for ex. (2, 4) -> (2, 9)
          if(first.first == second.first) {
            if(first.second < second.second) first.second++;
            else first.second--;
          }
          // for ex. (2, 4) -> (9, 4)
          else {
            if(first.first < second.first) first.first++;
            else first.first--;
          }
      }
      if(first == second) {
          std::pair<int, int> ins = std::make_pair(first.first, first.second);
          EnemySquare* new_square = new EnemySquare(ins.first, ins.second, std::vector<Enemy*>());
          if(first == second) enemy_path_.insert(std::make_pair(std::make_pair(ins.first, ins.second), new_square));
      }
    }
}

const std::map<std::pair<int, int>, MapSquare*>& LevelMap::GetSquares() const {
    return squares_;
}

const std::vector<Tower*>& LevelMap::GetTowers() const { 
    return towers_; 
}

const std::vector<Enemy*>& LevelMap::GetEnemies() const { 
    return enemies_; 
}

const MapSquare* LevelMap::GetSquare(int x, int y) const { 
    return squares_.at(std::make_pair(x, y)); 
}

const std::map<std::pair<int, int>, FreeSquare*> LevelMap::GetFreeSquares() const {
    std::map<std::pair<int, int>, FreeSquare*> list;
    for(auto it : squares_) {
      if(it.second->type() == "free") {
        std::pair<std::pair<int, int>, FreeSquare*> ins = std::make_pair(it.first, (FreeSquare*)it.second);
        list.insert(ins);
      }
    }
    std::cout << "Got squares of type FreeSquare, a total of " << list.size() << std::endl;
    return list;
  }

const std::map<std::pair<int, int>, TowerSquare*> LevelMap::GetTowerSquares() const {
    std::map<std::pair<int, int>, TowerSquare*> list;
    for(auto it : squares_) {
      if(it.second->type() == "tower") {
        std::pair<std::pair<int, int>, TowerSquare*> ins = std::make_pair(it.first, (TowerSquare*)it.second);
        list.insert(ins);
      }
    }
    std::cout << "Got squares of type TowerSquare, a total of " << list.size() << std::endl;
    return list;
}

const std::map<std::pair<int, int>, EnemySquare*> LevelMap::GetEnemySquares() const {
    std::map<std::pair<int, int>, EnemySquare*> list;
    for(auto it : squares_) {
      if(it.second->type() == "enemy") {
        std::pair<std::pair<int, int>, EnemySquare*> ins = std::make_pair(it.first, (EnemySquare*)it.second);
        list.insert(ins);
      }
    }
    std::cout << "Got squares of type EnemySquare, a total of " << list.size() << std::endl;
    return list;
}


const std::vector<Enemy*> LevelMap::EnemiesAt(int x, int y) const {
    const MapSquare* square = this->GetSquare(x, y);
    for(auto it : this->GetEnemySquares()) {
      if(it.second == square) return it.second->getEnemies();
    }
    return std::vector<Enemy*>();
}

const Tower& LevelMap::TowerAt(int x, int y) const {
    const MapSquare* square = this->GetSquare(x, y);
    for(auto it : this->GetTowerSquares()) {
      if(it.second == square) return it.second->getTower();
    }
    throw std::invalid_argument("No tower found!");
}

void LevelMap::ChangeSquare(int x, int y, MapSquare* new_square) {
    squares_.at(std::make_pair(x, y)) = new_square;
}

#endif