#include "Glue.hpp"
#include "Functions.hpp"
#include <vector>
#include <sstream>
#include <map>
using namespace std;


#define GAME_DELAY 10
#define IMG_PATH "Assets/towers"
#define IMG_EXTENSION ".png"
#define SHOOTING_DEALY 2000
#define BIULD_COST 60
#define DECREASE_SPEED_PERCENT 40
#define TIME_EFFECT 2500
#define UPGRADE_COST 45
#define UPGRADE_DAMAGE_PERCENT 10
#define UPGRADE_TIME_EFFECT 500
#define GLUE_BORDER_RADIUS 30



Glue::Glue(int level, Point point, vector<Enemy *> &enemies_) : Tower(DECREASE_SPEED_PERCENT, SHOOTING_DEALY, BIULD_COST, UPGRADE_COST, UPGRADE_DAMAGE_PERCENT, level, point)
{
    setEnemies(enemies_);
    timeEffect = TIME_EFFECT;
}

void Glue::setEnemies(vector<Enemy *> &enemies_)
{
    for (int i = 0; i < enemies_.size(); i++)
    {
        enemies.push_back(enemies_[i]);
    }
}

vector<Enemy *> Glue::getEnemiesInTerritory()
{
    vector<Enemy *> enemiesInBorder_;
    for (int i = 0; i < enemies.size(); i++)
    {
        if (isInBorder(enemies[i]))
        {
            enemiesInBorder_.push_back(enemies[i]);
        }
    }
    return enemiesInBorder_;
}

void Glue::damageEnemy()
{
    for (int i = 0; i < frameAndEnemies.size(); i++)
    {
        if (frameAndEnemies[i].first == (timeEffect / GAME_DELAY))
        {
            frameAndEnemies[i].second->getSpeedBackToNormal();
            frameAndEnemies.erase(frameAndEnemies.begin() + i);
            i--;
        }
    }
    if (bullet.hasEnemy())
    {
        vector<Enemy *> enemiesInBorder = getEnemiesInTerritory();
        if (bullet.isHitTheEnemy())
        {
            for (int i = 0; i < enemiesInBorder.size(); i++)
            {
                if (enemiesInBorder[i]->getSpeed() != 30)
                {
                    enemiesInBorder[i]->decreaseSpeed(damage);
                    frameAndEnemies.push_back(make_pair(0, enemiesInBorder[i]));
                }
            }
        }
    }
    for (int i = 0; i < frameAndEnemies.size(); i++)
    {
        frameAndEnemies[i].first++;
    }
}

bool Glue::isInBorder(Enemy *enemy_)
{
    FPoint centerEnemyPoint = bullet.getEnemysPoint();
    FPoint point = enemy_->getPoint();
    int deltaX = abs((int)centerEnemyPoint.x - (int)point.x);
    int deltaY = abs((int)centerEnemyPoint.y - (int)point.y);
    if (pow(GLUE_BORDER_RADIUS, 2) >= ((pow(deltaX, 2) + (pow(deltaY, 2)))))
    {
        return true;
    }
    return false;
}

void Glue::upgradeTower()
{

    if (level < 3)
    {
        damage += upgrade.increasedDamage;
        timeEffect += UPGRADE_TIME_EFFECT;
        level++;
    }
}

void Glue::draw(Window *window)
{
    Point center = getTheCenter(point);
    stringstream imagePath;
    imagePath << IMG_PATH<<"/"<< "glue" << level << IMG_EXTENSION;
    window->draw_img(imagePath.str(), Rectangle(center.x - 45, center.y - 45, 90, 90));
    bullet.draw(window);
}
