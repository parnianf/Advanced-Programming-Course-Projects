#include "Tower.hpp"
#include "Functions.hpp"



#define RADIUS_BORDER_PIXEL 150
#define DELAY 10


Tower::Tower(int damage_, int timeDelay_, int buildCost_, int upgradeCost, int increasedamage, int level_, Point point_)
    : bullet(getTheCenter(point_))
{
    damage = damage_;
    timeDelay = timeDelay_;
    buildCost = buildCost_;
    point = point_;
    level = level_;
    upgrade.cost = upgradeCost;
    upgrade.increasedDamage = increasedamage;
}
bool Tower::hasEnemy()
{
    if (bullet.hasEnemy())
    {
        return true;
    }
    return false;
}

int Tower::getUpgradingCost() { return upgrade.cost; }

int Tower::getLevel() { return level; }

Point Tower::getPoint()
{
    return point;
}

void Tower::shoot(int frame)
{

    if ((frame % (timeDelay / DELAY)) == 0)
    {
        allowShooting = true;
    }

    if (allowShooting)
    {
        if (bullet.hasEnemy())
        {
            bullet.move();
        }
    }
    stopShooting(allowShooting);
}

void Tower::stopShooting(bool &allowShooting)
{
    if (bullet.hasEnemy())
    {
        if (!isInTerritory(bullet.getEnemysPoint()))
        {
            bullet.reset();
            bullet.deletLastEnemy();
            allowShooting = false;
            return;
        }
        if (bullet.isInTerritory())
        {
            bullet.reset();
            allowShooting = false;
            return;
        }
    }
    if (!isInTerritory(bullet.getPoint()))
    {
        bullet.reset();
        allowShooting = false;
        return;
    }
}

void Tower::setEnemyForBullet(Enemy *enemy)
{
    bullet.setEnemy(enemy);
}

bool Tower::isInTerritory(FPoint enemyPoint)
{
    int deltaX = abs((int)enemyPoint.x - point.x);
    int deltaY = abs((int)enemyPoint.y - point.y);
    if (pow(RADIUS_BORDER_PIXEL, 2) >= ((pow(deltaX, 2) + (pow(deltaY, 2)))))
    {
        return true;
    }
    return false;
}
int Tower::getDelay() { return timeDelay; }
int Tower::getBuildCost() { return buildCost; }
