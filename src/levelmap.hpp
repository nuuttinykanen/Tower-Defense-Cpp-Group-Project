#include "mapsquare.hpp"
#include <vector>
#include <map>
#include <string>
class LevelMap {

  public:
  LevelMap(size_t size) : size_(size) {
    towers_ = std::vector<std::string>();
    enemies_ = std::vector<std::string>();
    squares_ = std::map<std::pair<int, int>, MapSquare*>();

    for(size_t i = 0; i < size; i++) {
      for(size_t j = 0; j < size; j++) {
        std::pair<int, int> coords = std::make_pair(i, j);
        MapSquare* new_square = new MapSquare();
        std::pair<std::pair<int, int>, MapSquare*> ins = std::make_pair(coords, new MapSquare());
        squares_.insert(ins);
      }
    }
  }

  
  
  std::map<std::pair<int, int>, MapSquare*>& GetSquares() { return squares_; }
  std::vector<std::string>& GetTowers() { return towers_; }
  std::vector<std::string>& GetEnemies()  { return enemies_; }
  MapSquare* GetSquare(int x, int y) const { return squares_.at(std::make_pair(x, y)); }

  private:
  size_t size_;
  std::map<std::pair<int, int>, MapSquare*> squares_;
  std::map<std::pair<int, int>, MapSquare*> enemy_path_;
  std::vector<std::string> towers_;
  std::vector<std::string> enemies_;
};
