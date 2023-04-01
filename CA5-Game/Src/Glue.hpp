#ifndef GLUE_H
#define GLUE_H "GLUE_H"

#include "rsdl.hpp"
#include "Tower.hpp"
#include "Enemy.hpp"
#include <map>
#include <functional>
#include <utility>
#include <vector>


class Glue : public Tower
{
public:
    Glue(int level, Point point, std::vector<Enemy *> &enemies_);
    void setEnemies(std::vector<Enemy *> &enemies_);
    std::vector<Enemy *> getEnemiesInTerritory();
    void damageEnemy();
    bool isInBorder(Enemy *enemy_);
    void upgradeTower();
    void draw(Window *window);

private:
    std::vector<Enemy *> enemies;
    std::vector<std::pair<int, Enemy *>> frameAndEnemies;
    int timeEffect;
};
#endif