#include "mapsquare.hpp"
#include <vector>
#include <map>
#include <string>
#include <iostream>
class LevelMap {

  public:
  // TODO: Path validity checks. 
  LevelMap(size_t size, std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> enemy_path) : size_(size) {
    towers_ = std::vector<std::string>();
    enemies_ = std::vector<std::string>();
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

    for(auto it : enemy_path_) {
        std::cout << it.first.first << " " << it.first.second << std::endl;
    }
    for(auto it : squares_) {
        std::cout << it.first.first << " " << it.first.second << std::endl;
    }
   }

  
  
  std::map<std::pair<int, int>, MapSquare*>& GetSquares() { return squares_; }
  std::vector<std::string>& GetTowers() { return towers_; }
  std::vector<std::string>& GetEnemies()  { return enemies_; }

  MapSquare* GetSquare(int x, int y) const { return squares_.at(std::make_pair(x, y)); }

  void ChangeSquare(int x, int y, MapSquare* new_square) {
    squares_.at(std::make_pair(x, y)) = new_square;
  }

  std::map<std::pair<int, int>, MapSquare*> GetSquaresOfType(std::string type) const {
    std::map<std::pair<int, int>, MapSquare*> list;
    for(auto it : squares_) {
      if(it.second->type() == type) {
        std::pair<std::pair<int, int>, MapSquare*> ins = std::make_pair(it.first, it.second);
        list.insert(ins);
      }
    }
    std::cout << "Got squares of type " << type << " a total of " << list.size() << std::endl;
    return list;
  }

  private:
  size_t size_;
  std::map<std::pair<int, int>, MapSquare*> squares_;
  std::map<std::pair<int, int>, EnemyPathSquare*> enemy_path_;
  std::pair<int, int> e_path_begin_;
  std::pair<int, int> e_path_end_;
  std::vector<std::string> towers_;
  std::vector<std::string> enemies_;
  std::vector<std::string> projectiles_;
};

