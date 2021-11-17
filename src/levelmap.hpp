#ifndef LEVELMAP_HPP
#define LEVELMAP_HPP

#include "mapsquare.hpp"
#include <vector>
#include <map>
#include <string>
#include <iostream>
#include "tower.hpp"
#include "enemy.hpp"
#include "projectile.hpp"
class LevelMap {

  public:
  // TODO: Path validity checks. 
  LevelMap(unsigned int size): size_(size) {
    towers_ = std::vector<Tower*>();
    enemies_ = std::vector<Enemy*>();
    squares_ = std::map<std::pair<int, int>, MapSquare*>();

    for(unsigned int i = 0; i < size; i++) {
      for(unsigned int j = 0; j < size; j++) {
        std::pair<int, int> coords = std::make_pair(i, j);
        FreeSquare* new_square = new FreeSquare(i, j);
        std::pair<std::pair<int, int>, FreeSquare*> ins = std::make_pair(coords, new FreeSquare(i, j));
        squares_.insert(ins); 
      }
    }
  }

  void InitializePath(std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> enemy_path);
  const std::map<std::pair<int, int>, MapSquare*>& GetSquares();
  const std::vector<Tower*>& GetTowers();
  const std::vector<Enemy*>& GetEnemies();
  MapSquare* GetSquare(int x, int y); 
  const std::map<std::pair<int, int>, FreeSquare*> GetFreeSquares();
  const std::map<std::pair<int, int>, TowerSquare*> GetTowerSquares();
  const std::map<std::pair<int, int>, EnemySquare*> GetEnemySquares();

  /*
  const std::map<std::pair<int, int>, EnemySquare*> GetPathStart() const;
  const std::map<std::pair<int, int>, EnemySquare*> GetPathEnd() const;
  */

  std::vector<Enemy*> EnemiesAt(int x, int y);
  Tower* TowerAt(int x, int y);
  void ChangeSquare(int x, int y, MapSquare* new_square);
  void MoveEnemy(Enemy* enemy, EnemySquare* start, EnemySquare* destination);
  void MoveEnemies();
  bool EraseEnemy(Enemy* enemy);
  bool PlaceEnemy(int x, int y, Enemy* enemy);
  EnemySquare* FindEnemy(Enemy* enemy);
  Enemy* GetFarthestEnemy();

  bool PlaceTower(int x, int y, Tower* tower);
  bool EraseTower(Tower* tower);
  TowerSquare* FindTower(Tower* tower);

  std::vector<Projectile*> GetProjectiles();
  void SetProjStartSquare(Projectile* projec);
  void PlaceProjectile(Projectile* projec);
  void RemoveProjectile(Projectile* projec);
  void ScanProjectiles();
  void MoveProjectiles();

  EnemySquare* GetProjTargetSquare(Projectile* proj);
  double ProjDistanceToTarget(Projectile* proj);
  void MoveProjectile(Projectile* proj); 

  private:
  size_t size_;
  std::map<std::pair<int, int>, MapSquare*> squares_;
  std::map<std::pair<int, int>, EnemySquare*> enemy_path_;
  std::vector<Tower*> towers_;
  std::vector<Enemy*> enemies_;
  std::vector<Projectile*> projectiles_;
};

#endif