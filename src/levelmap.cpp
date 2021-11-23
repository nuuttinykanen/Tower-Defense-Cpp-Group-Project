#ifndef LEVELMAP_CPP
#define LEVELMAP_CPP
#include "levelmap.hpp"
#include <cmath>
void LevelMap::InitializePath(std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> enemy_path) {
    EnemySquare* previous = nullptr;
    for(auto it : enemy_path) {
      std::pair<int, int> first = it.first;
      std::pair<int, int> second = it.second;
      while(first != second) {
          std::pair<int, int> ins = std::make_pair(first.first, first.second);
          EnemySquare* new_square = new EnemySquare(ins.first, ins.second);

          if(previous != nullptr) {
            new_square->SetPrevious(previous);
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
      new_square->SetPrevious(previous);
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

MapSquare* LevelMap::GetSquare(int x, int y) { 
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
      if(it.second->type() == "attack" || it.second->type() == "support") {
        std::pair<std::pair<int, int>, TowerSquare*> ins = std::make_pair(it.first, (TowerSquare*)it.second);
        list.insert(ins);
      }
    }
    return list;
}

const std::map<std::pair<int, int>, AttTowerSquare*> LevelMap::GetAttTowerSquares() {
    std::map<std::pair<int, int>, AttTowerSquare*> list;
    for(auto it : squares_) {
      if(it.second->type() == "attack") {
        std::pair<std::pair<int, int>, AttTowerSquare*> ins = std::make_pair(it.first, (AttTowerSquare*)it.second);
        list.insert(ins);
      }
    }
    return list;
}

const std::map<std::pair<int, int>, SuppTowerSquare*> LevelMap::GetSuppTowerSquares() {
    std::map<std::pair<int, int>, SuppTowerSquare*> list;
    for(auto it : squares_) {
      if(it.second->type() == "attack") {
        std::pair<std::pair<int, int>, SuppTowerSquare*> ins = std::make_pair(it.first, (SuppTowerSquare*)it.second);
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

EnemySquare* LevelMap::FindEnemy(Enemy* enemy) {
  auto s_enemies = this->GetEnemySquares();
  for(auto it = s_enemies.rbegin(); it != s_enemies.rend(); it++) {
    auto h = *it;
    if(h.second->ContainsEnemy(enemy)) {
      return h.second;
    }
  }
  return nullptr;
}

bool LevelMap::PlaceTower(int x, int y, Tower* tower) {
    auto t_squares = this->GetFreeSquares();
    for(auto it = t_squares.begin(); it != t_squares.end(); it++) {
      auto h = *it;
      if(h.first.first == x && h.first.second == y) {
        TowerSquare* t_square;
        if(tower->GetType() == "attack") t_square = new AttTowerSquare(x, y, (AttackTower*)tower);
        else t_square = new SuppTowerSquare(x, y, (SupportTower*)tower);
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
    }
  }
  return false;
}

TowerSquare* LevelMap::FindTower(Tower* tower) {
  auto towers = this->GetTowerSquares();
  for(auto it = towers.rbegin(); it != towers.rend(); it++) {
    auto h = *it;
    if(h.second->ContainsTower(tower)) {
      return h.second;
    }
  }
  return nullptr;
}

std::vector<Projectile*> LevelMap::GetProjectiles() { return projectiles_; }

void LevelMap::SetProjStartSquare(Projectile* proj) {
  TowerSquare* sender = this->FindTower(proj->GetSender());
  EnemySquare* t_location = this->GetProjTargetSquare(proj);
  MapSquare* new_square;
  if(t_location != nullptr) {
        double x_pow = pow(proj->GetLocation()->GetX() - t_location->GetX(), 2.0);
        double x_distance = sqrt(x_pow);
        double y_pow = pow(proj->GetLocation()->GetY() - t_location->GetY(), 2.0);
        double y_distance = sqrt(y_pow);

        // If diffx > diffy, either east or west
        std::string direction;
        if(x_distance > y_distance) {
            double west_x_dist = sqrt(pow(proj->GetLocation()->GetX() - 1 - t_location->GetX(), 2.0));
            double east_x_dist = sqrt(pow(proj->GetLocation()->GetX() + 1 - t_location->GetX(), 2.0));
            if(west_x_dist < east_x_dist) new_square = this->GetSquare(proj->GetLocation()->GetX() - 1, proj->GetLocation()->GetY());
            else new_square =                          this->GetSquare(proj->GetLocation()->GetX() + 1, proj->GetLocation()->GetY());
        } 
        else {
            double north_y_dist = sqrt(pow(proj->GetLocation()->GetY() + 1 - t_location->GetY(), 2.0));
            double south_y_dist = sqrt(pow(proj->GetLocation()->GetY() - 1 - t_location->GetY(), 2.0));
            if(north_y_dist < south_y_dist) new_square = this->GetSquare(proj->GetLocation()->GetX(), proj->GetLocation()->GetY() + 1);
            else                            new_square = this->GetSquare(proj->GetLocation()->GetX(), proj->GetLocation()->GetY() - 1);
        }
        if(new_square != nullptr) proj->ChangeLocation(new_square);
  }
}

Enemy* LevelMap::GetFarthestEnemy() {
  auto e_squares = this->GetEnemySquares();
  for(auto it = this->GetEnemySquares().rbegin(); it != this->GetEnemySquares().rend(); it++) {
    if(it->second->ContainsEnemies()) {
      return *(it->second->GetEnemies().begin());
    }
  }
  return nullptr;
}

void LevelMap::PlaceProjectile(Projectile* projec) { 
  this->SetProjStartSquare(projec);
  Enemy* farthest = this->GetFarthestEnemy();
  if(farthest != nullptr) projec->SetTarget(farthest);
  projectiles_.push_back(projec); 
}

void LevelMap::ScanProjectiles() {
  for(auto it = projectiles_.begin(); it != projectiles_.end(); it++) {
    Projectile* h = *it;
    if(h != nullptr && h->ToBeRemoved()) {
      projectiles_.erase(it);
      it--;
    }
  }
}
/*
  EnemySquare* GetProjTargetSquare(Projectile* proj);
  double ProjDistanceToTarget(Projectile* proj);
  void MoveProjec(Projectile* proj); 
*/
EnemySquare* LevelMap::GetProjTargetSquare(Projectile* proj) {
    return this->FindEnemy(proj->GetTarget());
}

double LevelMap::ProjDistanceToTarget(Projectile* proj) {
    EnemySquare* t_location = this->GetProjTargetSquare(proj);
    if(t_location != nullptr) {
      // std::cout << sqrt( pow(proj->GetLocation()->GetY() - t_location->GetY(), 2.0) + pow(proj->GetLocation()->GetX() - t_location->GetX(), 2.0) ) << " DISTANCE" << std::endl;
      return sqrt( pow(proj->GetLocation()->GetY() - t_location->GetY(), 2.0) + pow(proj->GetLocation()->GetX() - t_location->GetX(), 2.0) );
    }
    else return -1;
}

void LevelMap::MoveProjectile(Projectile* proj) {
    EnemySquare* t_location = this->GetProjTargetSquare(proj);
    MapSquare* new_square;
    if(t_location != nullptr) {
        double x_pow = pow(proj->GetLocation()->GetX() - t_location->GetX(), 2.0);
        double x_distance = sqrt(x_pow);
        double y_pow = pow(proj->GetLocation()->GetY() - t_location->GetY(), 2.0);
        double y_distance = sqrt(y_pow);

        // If diffx > diffy, either east or west
        std::string direction;
        if(x_distance > y_distance) {
            double west_x_dist = sqrt(pow(proj->GetLocation()->GetX() - 1 - t_location->GetX(), 2.0));
            double east_x_dist = sqrt(pow(proj->GetLocation()->GetX() + 1 - t_location->GetX(), 2.0));
            if(west_x_dist < east_x_dist) {
                // move west
                new_square = this->GetSquare(proj->GetLocation()->GetX() - 1, proj->GetLocation()->GetY());
            }
            else {
                // move east
                new_square = this->GetSquare(proj->GetLocation()->GetX() + 1, proj->GetLocation()->GetY());
            }
        } 
        else {
            double north_y_dist = sqrt(pow(proj->GetLocation()->GetY() + 1 - t_location->GetY(), 2.0));
            double south_y_dist = sqrt(pow(proj->GetLocation()->GetY() - 1 - t_location->GetY(), 2.0));
            if(north_y_dist < south_y_dist) {
                // move north
                new_square = this->GetSquare(proj->GetLocation()->GetX(), proj->GetLocation()->GetY() + 1);
            }
            else {
                new_square = this->GetSquare(proj->GetLocation()->GetX(), proj->GetLocation()->GetY() - 1);
            } 
        }
        if(new_square != nullptr) proj->ChangeLocation(new_square);

        if(ProjDistanceToTarget(proj) <= 1) {
            proj->SetRemovalTrue();
            proj->GetTarget()->ChangeHealth(-1 * proj->GetStrength());
        }
    }
}

void LevelMap::MoveProjectiles() {
  for(auto it : projectiles_) {
    this->MoveProjectile(it);
  }
  this->ScanProjectiles();
}


#endif