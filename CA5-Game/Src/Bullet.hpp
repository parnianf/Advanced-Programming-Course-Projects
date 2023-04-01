#ifndef Bullet_H
#define Bullet_H "Bullet_H"
#include"Enemy.hpp"
#include"rsdl.hpp"

class Bullet{

public:

    Bullet(Point originPoint_);
    FPoint getPoint();
    void draw(Window* window);
    void setEnemy(Enemy* enemy_);
    bool isHitTheEnemy();
    FPoint getEnemysPoint();
    void move();
    void reset();
    void deletLastEnemy();
    bool hasEnemy();
    void fadeIfDead();
    bool isInTerritory();
    void damageEnemy(float damage);
    float getEnemySpeed();

private:

Enemy* enemy;
FPoint point;
Point originPoint;
bool isHit;
};
#endif