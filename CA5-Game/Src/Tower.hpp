#ifndef TOWER_H
#define TOWER_H "TOWER_H"
#include "Bullet.hpp"
#include "rsdl.hpp"
#include "Enemy.hpp"
#include "FPoint.hpp"
class Bullet;

struct Upgrade
{
    int cost;
    int increasedDamage;
};

class Tower
{

public:
    Tower(int damage_, int timeDelay_, int buildCost_, int upgradeCost, int increasedamage, int level_, Point point_);
    bool hasEnemy();
    virtual void damageEnemy() = 0;
    int getLevel();
    int getUpgradingCost();
    Point getPoint();
    void shoot(int frame);
    void stopShooting(bool &allowShooting);
    void setEnemyForBullet(Enemy *enemy);
    virtual void draw(Window *window) = 0;
    virtual void upgradeTower() = 0;
    bool isInTerritory(FPoint enemyPoint);
    int getDelay();
    int getBuildCost();

protected:
    bool allowShooting;
    float damage;
    int timeDelay;
    int buildCost;
    int level;
    Point point;
    struct Upgrade upgrade;
    Bullet bullet;
};
#endif