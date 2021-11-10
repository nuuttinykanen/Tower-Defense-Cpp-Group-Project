#include "mapsquare.hpp"
#include <vector>
#include <map>
#include <string>
#include <iostream>
#include "tower.hpp"
#include "enemy.hpp"
class LevelMap {

  public:
  // TODO: Path validity checks. 
  LevelMap(size_t size, std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> enemy_path) : size_(size) {
    towers_ = std::vector<Tower*>();
    enemies_ = std::vector<Enemy*>();
    squares_ = std::map<std::pair<int, int>, MapSquare*>();
    e_path_begin_ = enemy_path.at(0).first;
    e_path_end_ = enemy_path.at(enemy_path.size() - 1).second;

    for(size_t i = 0; i < size; i++) {
      for(size_t j = 0; j < size; j++) {
        std::pair<int, int> coords = std::make_pair(i, j);
        FreeSquare* new_square = new FreeSquare(i, j);
        std::pair<std::pair<int, int>, FreeSquare*> ins = std::make_pair(coords, new FreeSquare(i, j));
        squares_.insert(ins);
      }
    }

    for(auto it : enemy_path) {
      std::pair<int, int> first = it.first;
      std::pair<int, int> second = it.second;
      while(first != second) {
          std::pair<int, int> ins = std::make_pair(first.first, first.second);
          EnemyPathSquare* new_square = new EnemyPathSquare(ins.first, ins.second);
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
          EnemyPathSquare* new_square = new EnemyPathSquare(ins.first, ins.second);
          if(first == second) enemy_path_.insert(std::make_pair(std::make_pair(ins.first, ins.second), new_square));
      }
    }
    this->GetEpathSquares();
    this->GetFreeSquares();
    this->GetEnemySquares();
    std::vector<Enemy*> enemies;
    Enemy* zombie = new Zombie;
    Enemy* myers = new MichaelMyers;
    enemies.push_back(zombie);
    enemies.push_back(myers);
    EnemySquare* e_square = new EnemySquare(0, 4, enemies);
    this->ChangeSquare(0, 4, e_square);
    for(auto it : this->EnemiesAt(0, 4)) {
      std::cout << it->GetName() << std::endl;
    }
    Tower* new_t = new Tower("SDADSA", 2, 5, 1, nullptr);
    TowerSquare* t_square = new TowerSquare(4, 4, *new_t);
    this->ChangeSquare(4, 4, t_square);

    this->GetTowerSquares();
   }

  
  
  std::map<std::pair<int, int>, MapSquare*>& GetSquares() { return squares_; }
  std::vector<Tower*>& GetTowers() { return towers_; }
  std::vector<Enemy*>& GetEnemies()  { return enemies_; }

  MapSquare* GetSquare(int x, int y) const { return squares_.at(std::make_pair(x, y)); }

  std::map<std::pair<int, int>, FreeSquare*> GetFreeSquares() const {
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

  std::map<std::pair<int, int>, TowerSquare*> GetTowerSquares() const {
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

  std::map<std::pair<int, int>, EnemySquare*> GetEnemySquares() const {
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

  std::map<std::pair<int, int>, EnemyPathSquare*> GetEpathSquares() const {
    std::map<std::pair<int, int>, EnemyPathSquare*> list;
    for(auto it : squares_) {
      if(it.second->type() == "epath") {
        std::pair<std::pair<int, int>, EnemyPathSquare*> ins = std::make_pair(it.first, (EnemyPathSquare*)it.second);
        list.insert(ins);
      }
    }
    std::cout << "Got squares of type EnemyPathSquare, a total of " << list.size() << std::endl;
    return list;
  }


  std::vector<Enemy*> EnemiesAt(int x, int y) {
    MapSquare* square = this->GetSquare(x, y);
    for(auto it : this->GetEnemySquares()) {
      if(it.second == square) return it.second->getEnemies();
    }
    return std::vector<Enemy*>();
  }

  Tower& TowerAt(int x, int y) {
    MapSquare* square = this->GetSquare(x, y);
    for(auto it : this->GetTowerSquares()) {
      if(it.second == square) return it.second->getTower();
    }
    throw std::invalid_argument("No tower found!");
  }

  void ChangeSquare(int x, int y, MapSquare* new_square) {
    squares_.at(std::make_pair(x, y)) = new_square;
  }

  private:
  size_t size_;
  std::map<std::pair<int, int>, MapSquare*> squares_;
  std::map<std::pair<int, int>, EnemyPathSquare*> enemy_path_;
  std::pair<int, int> e_path_begin_;
  std::pair<int, int> e_path_end_;
  std::vector<Tower*> towers_;
  std::vector<Enemy*> enemies_;
  std::vector<std::string> projectiles_;
};

