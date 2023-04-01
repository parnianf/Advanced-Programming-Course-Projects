#ifndef ENEMY_H
#define ENEMY_H "ENEMY_H"

#include "rsdl.hpp"
#include "FPoint.hpp"
#include <vector>

class Enemy
{
public:

    Enemy(int initialHealth_, int speed_, int moneyForKilling_, int takeHealth_);
    void setPoint(FPoint point_);
    void setDst(FPoint destination_);
    void fade();
    void setHeartInWave(int wave);
    void move();
    void moveXBackward();
    void moveYBackward();
    void moveXForward();
    void moveYForward();
    void decreaseHealth(float damage);
    void getSpeedBackToNormal();
    void decreaseSpeed(int damage);
    virtual void draw(Window *window) = 0;
    float getMoneyForKilling();
    float getTheTakeHealth();
    float getSpeed();
    bool yIsInTerritory(FPoint dst);
    bool xInTerritory(FPoint dst);
    bool isReachedDst();
    bool isMovingUp();
    bool isMovingDown();
    bool isMovingRight();
    bool isMovingLeft();
    bool isInEndOfPath(std::vector<FPoint> path);
    bool isInTerritory(FPoint dst);
    bool isEnemyDead();
    FPoint getPoint();
    FPoint getDst();
    void setP();

protected:
    float initialHealth;
    float health;
    float speed;
    float initialSpeed;
    float moneyForKilling;
    float takeHealth;
    FPoint point;
    FPoint destination;
};
#endif
