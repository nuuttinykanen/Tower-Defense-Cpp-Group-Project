#ifndef LEVELMAP_CPP
#define LEVELMAP_CPP
#include "levelmap.hpp"
#include <cmath>
void LevelMap::InitializePath(std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> enemy_path) {
    // validity check
    std::pair<std::pair<int, int>, std::pair<int, int>> previous_c = enemy_path.front();
    bool first = true;
    for(auto it : enemy_path) {
        std::pair<int, int> start = it.first;
        std::pair<int, int> end = it.second;
        if(!first) {
            std::pair<int, int> p_end = previous_c.second;
            if (start.first != p_end.first || start.second != p_end.second) {
                throw std::invalid_argument("The input path is not correct. Reason: input coordinates are not connected.");
            }
        }
        if(!((start.first == end.first && start.second != end.second) || (start.first != end.first && start.second == end.second))) {
            throw std::invalid_argument("The input path is not correct. Reason: input coordinates create a diagonal path.");
        }
        if(start.first >= this->size_ || start.second >= this->size_ || end.first >= this->size_ || end.second >= this->size_ || start.first < 0 || start.second < 0 || end.first < 0 || end.second < 0) {
            throw std::invalid_argument("The input path is out of bounds!");
        }
        if(first) first = false;
        previous_c = it;
    }

    EnemySquare* previous = nullptr;
    for(auto it : enemy_path) {
      std::pair<int, int> first = it.first;
      std::pair<int, int> second = it.second;
      while(first != second) {
          std::pair<int, int> ins = std::make_pair(first.first, first.second);
          auto* new_square = new EnemySquare(ins.first, ins.second);

          if(previous != nullptr) {
            new_square->SetPrevious(previous);
            previous->SetNext(new_square);
            new_square->SetNumber(previous->GetNumber());
          } else {
              new_square->SetNumber(0);
              this->start_square_ = new_square;
          }

          ChangeSquare(ins.first, ins.second, *new_square);
          enemy_path_.insert(std::make_pair(std::make_pair(ins.first, ins.second), new_square));

          // for ex. (2, 4) -> (2, 9)
          if(first.first == second.first) {
            if(first.second < second.second) first.second++;
            else first.second--;
          }
          // for ex. (2, 4) -> (9, 4)
          else {
              if (first.first < second.first) first.first++;
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
      this->end_square_ = new_square;
    }
    ChangeSquare(last.first, last.second, *new_square);
    this->enemy_path_.insert(std::make_pair(std::make_pair(last.first, last.second), new_square));
}

LevelMap::~LevelMap() {
    for(auto it : squares_) {
        delete(it.second);
    }
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
      if(it.second->GetType() == "free") {
        std::pair<std::pair<int, int>, FreeSquare*> ins = std::make_pair(it.first, (FreeSquare*)it.second);
        list.insert(ins);
      }
    }
    return list;
  }

const std::map<std::pair<int, int>, TowerSquare*> LevelMap::GetTowerSquares() {
    std::map<std::pair<int, int>, TowerSquare*> list;
    for(auto it : squares_) {
      if(it.second->GetType() == "tower") {
        std::pair<std::pair<int, int>, TowerSquare*> ins = std::make_pair(it.first, (TowerSquare*)it.second);
        list.insert(ins);
      }
    }
    return list;
}

  std::vector<TowerSquare*> LevelMap::GetAttackTowers() {
    std::vector<TowerSquare*> list;
    for(auto it : this->GetTowerSquares()) {
      if(it.second->GetTower()->GetType() == "attack") {
        list.push_back(it.second);
      }
    }
    return list;
  }

  std::vector<TowerSquare*> LevelMap::GetSupportTowers() {
    std::vector<TowerSquare*> list;
    for(auto it : this->GetTowerSquares()) {
        if(it.second->GetTower()->GetType() == "support") {
            list.push_back(it.second);
        }
    }
    return list;
}

const std::map<std::pair<int, int>, EnemySquare*> LevelMap::GetEnemySquares() {
    std::map<std::pair<int, int>, EnemySquare*> list;
    for(auto it : squares_) {
      if(it.second->GetType() == "enemy") {
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

unsigned int LevelMap::GetEnemyAmount() {
    return enemy_count_;
}

Tower* LevelMap::TowerAt(int x, int y) {
    const MapSquare* square = this->GetSquare(x, y);
    for(auto it : this->GetTowerSquares()) {
      if(it.second == square) return it.second->GetTower();
    }
    throw std::invalid_argument("No tower found!");
}

void LevelMap::ChangeSquare(int x, int y, MapSquare& new_square) {
    auto pair = std::make_pair(x, y);
    auto target = squares_.find(pair);
    if(target != squares_.end()) {
        auto removal = target->second;
        target->second = &new_square;
        delete(removal);
    }
}

const MapSquare* LevelMap::GetStartSquare() {
    return this->start_square_;
}

const MapSquare* LevelMap::GetEndSquare() {
    return this->end_square_;
}

bool LevelMap::PlaceEnemy(int x, int y, Enemy& enemy) {
    auto e_squares = this->GetEnemySquares();
    for(auto h : e_squares) {
      if(h.first.first == x && h.first.second == y) {
        h.second->AddEnemy(&enemy);
        enemy.SetOnMap();
        this->enemy_count_ += 1;
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
        this->enemy_count_ -= 1;
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
      if(e->GetHealth() < 1) {
        e->RemoveFromMap();
        this->EraseEnemy(e);
      }
      else {
          e->ProgressCooldown();
        if(e->GetCooldown() <= 0) {
            if(!h.second->HasNext()) {
                this->EraseEnemy(e);
                e->RemoveFromMap();
                this->enemies_passed_ += 1;
            }
            else {
                this->MoveEnemy(e, h.second, h.second->GetNext());
                e->ResetCooldownModifier();
                e->ChangeCooldown(e->GetSpeed());
            }
        }

        /*EnemySquare* destination = h.second->GetNext();
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
          e->RemoveFromMap();
          this->enemies_passed_ += 1;
        } else {
          this->MoveEnemy(e, h.second, destination);
        }*/
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
        t_square = new TowerSquare(x, y, tower);

        // Scan for enemy squares in range
        Tower* tower = t_square->GetTower();
        unsigned int range = tower->GetRange();
        for(auto en : this->GetEnemySquares()) {
            double dist = sqrt(pow(en.second->GetX() - t_square->GetX(), 2.0) + pow(en.second->GetY() - t_square->GetY(), 2.0));
            if(dist <= (double)range) {
                t_square->AddToEnemiesInRange(en.second);
            }
        }
        this->ChangeSquare(x, y, *t_square);
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
        this->ChangeSquare(h.second->GetX(), h.second->GetY(), *f_square);
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

void LevelMap::UpgradeTowerSquare(TowerSquare *tsq) {
    if(tsq == nullptr) return;
    auto upgrade = tsq->GetTower()->Upgrade();
    if(upgrade == nullptr) return;
    int x = tsq->GetX();
    int y = tsq->GetY();
    this->EraseTower(tsq->GetTower());
    this->PlaceTower(x, y, upgrade);
}

std::vector<Projectile*> LevelMap::GetProjectiles() { return projectiles_; }

MapSquare* LevelMap::GetNextMoveSquare(MapSquare* start, MapSquare* end) {
    MapSquare* new_square;
    if(start != nullptr && end != nullptr) {
        int x1 = start->GetX();
        int y1 = start->GetY();
        int x2 = end->GetX();
        int y2 = end->GetY();

        double x_distance = sqrt(pow(x2 - x1, 2.0));
        double y_distance = sqrt(pow(y2 - y1, 2.0));

        // If diffx > diffy, either east or west
        if(x_distance > y_distance) {
            double west_x_dist = sqrt(pow(x1 - 1 - x2, 2.0));
            double east_x_dist = sqrt(pow(x1 + 1 - x2, 2.0));
            if(west_x_dist < east_x_dist) {
                // move west
                new_square = this->GetSquare(x1 - 1, y1);
            }
            else {
                // move east
                new_square = this->GetSquare(x1 + 1, y1);
            }
        } 
        else {
            double north_y_dist = sqrt(pow(y1 + 1 - y2, 2.0));
            double south_y_dist = sqrt(pow(y1 - 1 - y2, 2.0));
            if(north_y_dist < south_y_dist) {
                // move north
                new_square = this->GetSquare(x1, y1 + 1);
            }
            else {
                new_square = this->GetSquare(x1, y1 - 1);
            } 
        }
    }
    return new_square;
}

MapSquare* LevelMap::GetProjStartSquare(TowerSquare* tower, Enemy* enemy) {
  EnemySquare* target = this->FindEnemy(enemy);
  return this->GetNextMoveSquare(tower, target);
}

EnemySquare* LevelMap::GetFarthestEnemy(std::vector<EnemySquare*> list) {
    for(auto it = list.rbegin(); it != list.rend(); it++) {
        auto es = *it;
        if (es->ContainsEnemies()) {
            return es;
        }
    }
    return nullptr;
}

void LevelMap::ShootProjectile(TowerSquare* sender) {
    Tower* tower = sender->GetTower();
    if(tower->GetType() != "attack") return;

    EnemySquare* target_s = this->GetFarthestEnemy(sender->EnemySquaresInRange());
    if(target_s == nullptr || !target_s->ContainsEnemies()) return;
    Enemy* target = *(target_s->GetEnemies().begin());
    MapSquare* start = this->GetProjStartSquare(sender, target);
    if(start == nullptr) return;

    auto att_tower = (AttackTower*)tower;
    Projectile* new_projec = att_tower->GetProjectile();
    new_projec->Initialize(start, target);
    projectiles_.push_back(new_projec);
    att_tower->RestartCooldown();
}


void LevelMap::ScanProjectiles() {
  for(auto it = projectiles_.begin(); it != projectiles_.end(); it++) {
    Projectile* h = *it;
    if(h != nullptr && h->ToBeRemoved()) {
      projectiles_.erase(it);
      delete(h);
      it--;
    }
  }
}

EnemySquare* LevelMap::GetTargetSquare(Projectile* proj) {
    if(proj->GetTarget() != nullptr) {
      Enemy* targ = proj->GetTarget();
      return this->FindEnemy(targ);
    }
    else {
      return nullptr;
    }
}

double LevelMap::ProjDistanceToTarget(Projectile* proj) {
    EnemySquare* t_location = this->GetTargetSquare(proj);
    if(t_location != nullptr) {
        double ydiff = (double)proj->GetLocation()->GetY() - (double)t_location->GetY();
        double xdiff = (double)proj->GetLocation()->GetX() - (double)t_location->GetX();
        double dist = (double)sqrt((double)pow(ydiff, 2.0) + (double)pow(xdiff, 2.0) );
        return dist;
    }
    else return -1.0;
}

void LevelMap::MoveProjectile(Projectile* proj) {
    EnemySquare* target_s = this->GetTargetSquare(proj);
    MapSquare* new_square = this->GetNextMoveSquare(proj->GetLocation(), target_s);
    if(new_square == nullptr) return;
    proj->ChangeLocation(new_square);
    std::cout << (double)ProjDistanceToTarget(proj) << std::endl;
    if(ProjDistanceToTarget(proj) <= 1) {
      proj->Effect(this->GetTargetSquare(proj));
    }
}

void LevelMap::MoveProjectiles() {
  for(auto it : projectiles_) {
    if(it->GetTarget()->OnMap()) this->MoveProjectile(it);
    else it->SetRemovalTrue();
  }
  this->ScanProjectiles();
}

unsigned int LevelMap::GetEnemiesPassed() {
  return this->enemies_passed_;
}

const std::map<std::pair<int, int>, MapSquare *> &LevelMap::GetSquares() {
    return squares_;
}


#endif