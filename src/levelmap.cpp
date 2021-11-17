#ifndef LEVELMAP_CPP
#define LEVELMAP_CPP
#include "levelmap.hpp"

void LevelMap::InitializePath(std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> enemy_path) {
    EnemySquare* previous;
    for(auto it : enemy_path) {
      std::pair<int, int> first = it.first;
      std::pair<int, int> second = it.second;
      while(first != second) {
          std::pair<int, int> ins = std::make_pair(first.first, first.second);
          EnemySquare* new_square = new EnemySquare(ins.first, ins.second);

          if(previous != nullptr) {
            previous->SetNext(new_square);
          }

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
          previous = new_square;
      }
    }
    std::pair<int, int> last = enemy_path.back().second;
    EnemySquare* new_square = new EnemySquare(last.first, last.second);
    if(previous != nullptr) {
      previous->SetNext(new_square);
    }
    ChangeSquare(last.first, last.second, new_square);
    this->enemy_path_.insert(std::make_pair(std::make_pair(last.first, last.second), new_square));
}

const std::map<std::pair<int, int>, MapSquare*>& LevelMap::GetSquares() {
    return squares_;
}

const std::vector<Tower*>& LevelMap::GetTowers() { 
    return towers_; 
}

const std::vector<Enemy*>& LevelMap::GetEnemies() { 
    return enemies_; 
}

const MapSquare* LevelMap::GetSquare(int x, int y) { 
    return squares_.at(std::make_pair(x, y)); 
}

const std::map<std::pair<int, int>, FreeSquare*> LevelMap::GetFreeSquares() {
    std::map<std::pair<int, int>, FreeSquare*> list;
    for(auto it : squares_) {
      if(it.second->type() == "free") {
        std::pair<std::pair<int, int>, FreeSquare*> ins = std::make_pair(it.first, (FreeSquare*)it.second);
        list.insert(ins);
      }
    }
    return list;
  }

const std::map<std::pair<int, int>, TowerSquare*> LevelMap::GetTowerSquares() {
    std::map<std::pair<int, int>, TowerSquare*> list;
    for(auto it : squares_) {
      if(it.second->type() == "tower") {
        std::pair<std::pair<int, int>, TowerSquare*> ins = std::make_pair(it.first, (TowerSquare*)it.second);
        list.insert(ins);
      }
    }
    return list;
}

const std::map<std::pair<int, int>, EnemySquare*> LevelMap::GetEnemySquares() {
    std::map<std::pair<int, int>, EnemySquare*> list;
    for(auto it : squares_) {
      if(it.second->type() == "enemy") {
        std::pair<std::pair<int, int>, EnemySquare*> ins = std::make_pair(it.first, (EnemySquare*)it.second);
        list.insert(ins);
      }
    }
    return list;
}


std::vector<Enemy*> LevelMap::EnemiesAt(int x, int y) {
    const MapSquare* square = this->GetSquare(x, y);
    for(auto it : this->GetEnemySquares()) {
      if(it.second == square) return it.second->GetEnemies();
    }
    return std::vector<Enemy*>();
}

Tower* LevelMap::TowerAt(int x, int y) {
    const MapSquare* square = this->GetSquare(x, y);
    for(auto it : this->GetTowerSquares()) {
      if(it.second == square) return it.second->GetTower();
    }
    throw std::invalid_argument("No tower found!");
}

void LevelMap::ChangeSquare(int x, int y, MapSquare* new_square) {
    squares_.at(std::make_pair(x, y)) = new_square;
}

bool LevelMap::PlaceEnemy(int x, int y, Enemy* enemy) {
    auto e_squares = this->GetEnemySquares();
    for(auto it = e_squares.begin(); it != e_squares.end(); it++) {
      auto h = *it;
      if(h.first.first == x && h.first.second == y) {
        h.second->AddEnemy(enemy);
        return true;
      }
    }
    return false;
}

bool LevelMap::EraseEnemy(Enemy* enemy) {
  auto s_enemies = this->GetEnemySquares();
  for(auto it = s_enemies.rbegin(); it != s_enemies.rend(); it++) {
    auto h = *it;
    if(h.second->ContainsEnemy(enemy)) {
      h.second->RemoveEnemy(enemy);
      return true;
    }
  }
  return false;
}

void LevelMap::MoveEnemy(Enemy* enemy, EnemySquare* start, EnemySquare* destination) {
  auto s_enemies = this->GetEnemySquares();
  for(auto it = s_enemies.begin(); it != s_enemies.end(); it++) {
    auto h = *it;
    if(h.second == destination) {
      if(enemy != nullptr) {
        start->RemoveEnemy(enemy);
        destination->AddEnemy(enemy);
      }
    }
  }
  for(auto it = s_enemies.begin(); it != s_enemies.end(); it++) {
    auto h = *it;
    if(h.second == destination) {
      if(enemy != nullptr) {
        h.second->RemoveEnemy(enemy);
        destination->AddEnemy(enemy);
      }
    }
  }
}

void LevelMap::MoveEnemies() {
  auto e_squares = this->GetEnemySquares();
  for(auto it = e_squares.rbegin(); it != e_squares.rend(); it++) {
    auto h = *it;
    auto enemies = h.second->GetEnemies();
    for(auto et = enemies.begin(); et != enemies.end(); et++) {
      auto e = *et;
      EnemySquare* destination = h.second->GetNext();
      bool end = false;
      if(destination == nullptr) end = true;
      for(int i = 1; i < e->GetSpeed(); i++) {
        if(destination != nullptr && destination->HasNext()) destination = destination->GetNext();
        else {
          end = true;
          break;
        }
      }
      if(end) {
        this->EraseEnemy(e);
      } else {
        this->MoveEnemy(e, h.second, destination);
      }
    }
  } 
}

bool LevelMap::PlaceTower(int x, int y, Tower* tower) {
    auto t_squares = this->GetFreeSquares();
    for(auto it = t_squares.begin(); it != t_squares.end(); it++) {
      auto h = *it;
      if(h.first.first == x && h.first.second == y) {
        TowerSquare* t_square = new TowerSquare(x, y, tower);
        this->ChangeSquare(x, y, t_square);
        return true;
      }
    }
    return false;
}

bool LevelMap::EraseTower(Tower* tower) {
  auto t_squares = this->GetTowerSquares();
  for(auto it = t_squares.rbegin(); it != t_squares.rend(); it++) {
    auto h = *it;
    if(h.second->ContainsTower(tower)) { 
        FreeSquare* f_square = new FreeSquare(h.second->GetX(), h.second->GetY());
        this->ChangeSquare(h.second->GetX(), h.second->GetY(), f_square);
        return true;
      return true;
    }
  }
  return false;
}

#endif