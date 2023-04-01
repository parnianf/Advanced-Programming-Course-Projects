#ifndef MISSILE_H
#define MISSILE_H "MISSILE_H"

#include"rsdl.hpp"
#include"Tower.hpp"
#include<vector>
class Missile : public Tower{
public:
    Missile(int level,Point point,std::vector<Enemy*>& enemies_);
    void setEnemies(std::vector<Enemy*>& enemies_);

    std::vector<Enemy*> getEnemiesInTerritory();

    virtual void damageEnemy();

    bool isInBorder(Enemy* enemy_);

    virtual void upgradeTower();

    void draw(Window* window);
private:
std::vector<Enemy*> enemies;
};
#endif