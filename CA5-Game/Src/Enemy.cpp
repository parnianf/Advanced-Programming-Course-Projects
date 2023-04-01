#include "Enemy.hpp"
#include <cmath>
#include <sstream>
#include "rsdl.hpp"
using namespace std;


#define DELAY 10
#define ERROR_IN_PIXELS 1



Enemy::Enemy(int initialHealth_, int speed_, int moneyForKilling_, int takeHealth_)
{
    initialHealth = initialHealth_;
    speed = speed_;
    initialSpeed = speed_;
    moneyForKilling = moneyForKilling_;
    takeHealth = takeHealth_;
    health = initialHealth_;
}

bool Enemy::isEnemyDead()
{
    if (health <= 0)
    {
        fade();
        return true;
    }
    return false;
}

float Enemy::getSpeed()
{
    return speed;
}

void Enemy::setPoint(FPoint point_)
{
    point = point_;
}
void Enemy::setDst(FPoint destination_)
{
    destination = destination_;
}
FPoint Enemy::getPoint()
{
    return point;
}
FPoint Enemy::getDst() { return destination; }

bool Enemy::isInEndOfPath(vector<FPoint> path)
{
    if (isInTerritory(path[path.size() - 1]))
    {
        fade();
        return true;
    }
    return false;
}

bool Enemy::isInTerritory(FPoint dst)
{
    float deltaX = dst.x - point.x;
    float deltaY = dst.y - point.y;
    if (pow(ERROR_IN_PIXELS, 2) >= (powf(deltaX, 2) + (powf(deltaY, 2))))
    {
        return true;
    }
    return false;
}

void Enemy::fade()
{
    point.x = 2000;
    point.y = 2000;
}

void Enemy::setP(){
    float deltaX = destination.x - point.x;
    float deltaY = destination.y - point.y;
    if (pow(ERROR_IN_PIXELS, 2) >= (powf(deltaX, 2) + (powf(deltaY, 2))))
    {
        point.x = destination.x;
        point.y = destination.y; 
    }
}


void Enemy::setHeartInWave(int wave)
{
    if (wave == 0)
    {
        return;
    }
    wave++;
    health = ((0.9 + (wave * 0.1)) * initialHealth);
    initialHealth = health;
}

bool Enemy::isReachedDst()
{

    if (isInTerritory(destination))
    {
        return true;
    }
    return false;
}
bool Enemy::xInTerritory(FPoint dst)
{
    float deltaX = abs(dst.x - point.x);
    if (deltaX <= ERROR_IN_PIXELS)
    {
        return true;
    }
    return false;
}
bool Enemy::yIsInTerritory(FPoint dst)
{
    float deltaY = abs(dst.y - point.y);
    if (deltaY <= ERROR_IN_PIXELS)
    {
        return true;
    }
    return false;
}
void Enemy::move()
{
    if (xInTerritory(destination))
    {
        if (isMovingUp())
        {
            moveYForward();
        }
        else if (isMovingDown())
        {
            moveYBackward();
        }
    }

    else if (yIsInTerritory(destination))
    {
        if (isMovingRight())
        {
            moveXForward();
        }
        else if (isMovingLeft())
        {
            moveXBackward();
        }
    }
}

bool Enemy::isMovingUp()
{
    if ((int)point.y < destination.y)
    {
        return true;
    }
    return false;
}
bool Enemy::isMovingDown()
{
    if ((int)point.y > destination.y)
    {
        return true;
    }
    return false;
}

bool Enemy::isMovingRight()
{
    if ((int)point.x < destination.x)
    {
        return true;
    }
    return false;
}
bool Enemy::isMovingLeft()
{
    if ((int)point.x > destination.x)
    {
        return true;
    }
    return false;
}

void Enemy::moveXBackward()
{
    point.x -= speed * DELAY / 1000;
    point.x = roundf(point.x * 10) / 10;
}
void Enemy::moveYBackward()
{
    point.y -= speed * DELAY / 1000;
        point.y = roundf(point.y * 10) / 10;

}
void Enemy::moveXForward()
{
    point.x += speed * DELAY / 1000;
    point.x = roundf(point.x * 10) / 10;
}
void Enemy::moveYForward()
{
    point.y += speed * DELAY / 1000;
        point.y = roundf(point.y * 10) / 10;

}

void Enemy::decreaseHealth(float damage)
{
    health -= damage;
}

float Enemy::getMoneyForKilling()
{
    return moneyForKilling;
}

float Enemy::getTheTakeHealth()
{
    return takeHealth;
}

void Enemy::getSpeedBackToNormal()
{
    speed = initialSpeed;
}

void Enemy::decreaseSpeed(int decreaseSpeedPercent)
{
    speed = ((100 - (float)decreaseSpeedPercent) * initialSpeed) / 100;
}
