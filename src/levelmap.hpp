#ifndef LEVELMAP_HPP
#define LEVELMAP_HPP

#include "mapsquare.hpp"
#include <vector>
#include <map>
#include <string>
#include <iostream>
#include "towers/tower.hpp"
#include "enemy.hpp"
#include "projectile.hpp"
#include "towers/attacktower.hpp"
#include "towers/supporttower.hpp"
class LevelMap {

  public:
  // TODO: Path validity checks. 
  LevelMap(unsigned int width, unsigned int height, int levelNumber): width_(width), height_(height), levelNumber_(levelNumber) {
    towers_ = std::vector<Tower*>();
    enemies_ = std::vector<Enemy*>();
    squares_ = std::map<std::pair<int, int>, MapSquare*>();
    enemies_passed_ = 0;
    enemy_count_ = 0;
    start_square_ = nullptr;
    end_square_ = nullptr;
    projectileMarks_ = std::vector<std::pair<std::string, std::vector<std::pair<int, int>>>>();

    for(unsigned int i = 0; i < width; i++) {
      for(unsigned int j = 0; j < height; j++) {
        std::pair<int, int> coords = std::make_pair(i, j);
        FreeSquare* new_square = new FreeSquare(i, j);
        std::pair<std::pair<int, int>, FreeSquare*> ins = std::make_pair(coords, new FreeSquare(i, j));
        squares_.insert(ins); 
      }
    }

  }
  ~LevelMap();
  void InitializePath(std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> enemy_path);
  int getLevelNumber() {return levelNumber_;}
  const MapSquare* GetStartSquare();
  const MapSquare* GetEndSquare();
  const std::map<std::pair<int, int>, MapSquare*>& GetSquares();
  const std::vector<Tower*>& GetTowers() {return towers_;};
  const std::vector<Enemy*>& GetEnemies();
  MapSquare* GetSquare(int x, int y); 
  const std::map<std::pair<int, int>, FreeSquare*> GetFreeSquares();
  const std::map<std::pair<int, int>, TowerSquare*> GetTowerSquares();
  const std::map<std::pair<int, int>, EnemySquare*> GetEnemySquares();
  std::vector<TowerSquare*> GetAttackTowers();
  std::vector<TowerSquare*> GetSupportTowers();
  std::vector<std::pair<std::string, std::vector<std::pair<int, int>>>> GetProjectileMarks();


  std::vector<Enemy*> EnemiesAt(int x, int y);
  Tower* TowerAt(int x, int y);
  void ChangeSquare(int x, int y, MapSquare& new_square);
  void MoveEnemy(Enemy* enemy, EnemySquare* start, EnemySquare* destination);
  void MoveEnemies();
  bool EraseEnemy(Enemy* enemy);
  bool PlaceEnemy(int x, int y, Enemy& enemy);
  EnemySquare* FindEnemy(Enemy* enemy);
  EnemySquare* GetFarthestEnemy(std::vector<EnemySquare*> list);
  MapSquare* GetNextMoveSquare(MapSquare* start, MapSquare* end);
  unsigned int GetEnemyAmount();

  bool PlaceTower(int x, int y, Tower* tower);
  void EraseTowerAt(TowerSquare *towerSquare);
  TowerSquare* FindTower(Tower* tower);

  std::vector<Projectile*> GetProjectiles();
  MapSquare* GetProjStartSquare(TowerSquare* t_square, Enemy* enemy);
  void PlaceProjectile(Projectile* projec);
  void ShootProjectile(TowerSquare* sender);
  void RemoveProjectile(Projectile* projec);
  void ScanProjectiles();
  void MoveProjectiles();

  EnemySquare* GetTargetSquare(Projectile* proj);
  double ProjDistanceToTarget(Projectile* proj);
  void MoveProjectile(Projectile* proj); 

  unsigned int GetEnemiesPassed();

  private:
  size_t size_;
  int width_;
  int height_;
  int levelNumber_;
  std::map<std::pair<int, int>, MapSquare*> squares_;
  std::map<std::pair<int, int>, EnemySquare*> enemy_path_;
  std::vector<Tower*> towers_;
  std::vector<Enemy*> enemies_;
  std::vector<Projectile*> projectiles_;
  unsigned int enemy_count_;
  unsigned int enemies_passed_;
  std::vector<std::pair<std::string, std::vector<std::pair<int, int>>>> projectileMarks_;
  const MapSquare* start_square_;
  const MapSquare* end_square_;
};

#endif