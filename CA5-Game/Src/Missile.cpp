#include"Missile.hpp"
#include"Functions.hpp"
#include<sstream>
using namespace std;




#define IMG_PATH "Assets/towers"
#define IMG_EXTENSION ".png"
#define SHOOTING_DEALY 3000
#define BIULD_COST 70
#define DAMAGE 75
#define UPGRADE_COST 60
#define UPGRADE_DAMAGE 75
#define BULLETS_EFFECT_BORDER_RADIUS 50



Missile::Missile(int level,Point point,vector<Enemy*>& enemies_) : Tower(DAMAGE,SHOOTING_DEALY,BIULD_COST,UPGRADE_COST,UPGRADE_DAMAGE,level,point){
    setEnemies(enemies_);
    
}
void Missile::setEnemies(vector<Enemy*>& enemies_){
    for(int i=0;i<enemies_.size();i++){
        enemies.push_back(enemies_[i]);
    }
}

vector<Enemy*>Missile::getEnemiesInTerritory(){
    vector<Enemy*> enemiesInBorder_;
    for(int i=0;i<enemies.size();i++){
        if(isInBorder(enemies[i])){
            enemiesInBorder_.push_back(enemies[i]);
        }
    }
    return enemiesInBorder_;
}

void Missile::damageEnemy(){
    if(bullet.hasEnemy()){
        vector<Enemy*> enemiesInBorder = getEnemiesInTerritory();
        if(bullet.isHitTheEnemy()){
            for(int i=0;i<enemiesInBorder.size();i++){
                enemiesInBorder[i]->decreaseHealth(damage);
                    enemies[i]->isEnemyDead();
            }
        }
    }
}

bool Missile::isInBorder(Enemy* enemy_){
    FPoint centerEnemyPoint = bullet.getEnemysPoint();
    FPoint point = enemy_->getPoint();
    int deltaX = abs((int)centerEnemyPoint.x - (int)point.x);
    int deltaY = abs((int)centerEnemyPoint.y - (int)point.y); 
    if(pow(BULLETS_EFFECT_BORDER_RADIUS,2) >= ((pow(deltaX,2) + (pow(deltaY,2))))) {
        return true;
    }
    return false;
}

void Missile::upgradeTower(){
    if(level < 3){
        damage += upgrade.increasedDamage;
        level++;
    }
        
}

void Missile::draw(Window* window){
    Point center = getTheCenter(point);
    stringstream imagePath;
    imagePath<<IMG_PATH<<"/" <<"missile" << level<<IMG_EXTENSION;
    window->draw_img(imagePath.str(),Rectangle(center.x-45,center.y-45,90,90));
    bullet.draw(window);
}
