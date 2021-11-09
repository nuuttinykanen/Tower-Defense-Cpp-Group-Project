#include "mapsquare.hpp"
#include <vector>
#include <map>
#include <string>
#include <iostream>
class LevelMap {

  public:
  LevelMap(size_t size, std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> enemy_path) : size_(size) {
    towers_ = std::vector<std::string>();
    enemies_ = std::vector<std::string>();
    squares_ = std::map<std::pair<int, int>, FreeSquare*>();
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
          std::cout << "awnfsaijnfkljsdnfldsjk " << std::endl;
          if(first.second < second.second) first.second++;
          else first.second--;
        }
        // for ex. (2, 4) -> (9, 4)
        else {
          if(first.first < second.first) first.first++;
          else first.first--;
        }
      }
    }
   }

  
  
  std::map<std::pair<int, int>, FreeSquare*>& GetSquares() { return squares_; }
  std::vector<std::string>& GetTowers() { return towers_; }
  std::vector<std::string>& GetEnemies()  { return enemies_; }

  MapSquare* GetSquare(int x, int y) const { return squares_.at(std::make_pair(x, y)); }

  void ChangeSquare(int x, int y, MapSquare* new_square) {
    MapSquare* prev_square = GetSquare(x, y);
    prev_square = new_square;
  }

  private:
  size_t size_;
  std::map<std::pair<int, int>, FreeSquare*> squares_;
  std::map<std::pair<int, int>, EnemyPathSquare*> enemy_path_;
  std::pair<int, int> e_path_begin_;
  std::pair<int, int> e_path_end_;
  std::vector<std::string> towers_;
  std::vector<std::string> enemies_;
  std::vector<std::string> projectiles_;
};
