#ifndef FIELDRUNNERS_H
#define FIELDRUNNERS_H "FIELDRUNNERS_H"

#include "rsdl.hpp"
#include "FPoint.hpp"
#include "Player.hpp"
#include <vector>

class Tower;
class Enemy;

class FieldRunners
{
public:
    void createTower(char towerType, Point newTowerPoint);
    int getenemiesVectorIndex(Enemy *removedEnemy);
    void setEnemies(std::vector<Enemy *> allenemies);
    void handlePlayer(std::vector<FPoint> coordinates);
    void moveBullets(int frame);
    void handleEnemyHealth();
    Enemy *getNearestEnemy(Tower *centerTower);
    void setEnemiesInBattle();
    void draw(Window *window);
    Tower *findTowerByPoint(Point p);
    void handleMoney();
    void handleHearts(std::vector<FPoint> coordinates);
    void moveEnemies(std::vector<FPoint> coordinates,const int &frame);
    bool isWaveFinished();
    void updateEvent(Window *window);
    void creatEnemies(std::vector<std::vector<int>> enemiesNumber, int wave);
    void lose(Window *window, int currentWave, int totalWave);
    void win(Window *window, int currentWave, int totalWave);
    void processGame(std::vector<FPoint> coordinates,const int frame);
    void winOrLose(Window *window, int currentWave, int totalWave);
private:
    std::vector<Tower *> towers;
    std::vector<Enemy *> enemies;
    std::vector<Enemy *> enemiesInBattle;
    Player player;
};
#endif
