#include"Gatling.hpp"
#include"Functions.hpp"
#include<sstream>
using namespace std;


#define IMG_PATH "Assets/towers"
#define IMG_EXTENSION ".png"
#define SHOOTING_DEALY 1000
#define BIULD_COST 55
#define DAMAGE 35
#define UPGRADE_COST 40
#define UPGRADE_DAMAGE 35

Gatling::Gatling(int level,Point point) : Tower(DAMAGE,SHOOTING_DEALY,BIULD_COST,UPGRADE_COST,UPGRADE_DAMAGE,level,point){

}

void Gatling::damageEnemy(){
    
    if(bullet.hasEnemy()){
        if(bullet.getEnemySpeed() == 30){
            return;
        }
        if(bullet.isHitTheEnemy()){
            bullet.damageEnemy(damage);
            bullet.fadeIfDead();
        }
    }
}

void Gatling::upgradeTower(){
    if(level < 3){
        damage += upgrade.increasedDamage;
        level++;
    }
}
void Gatling::draw(Window* window) { 
    Point center = getTheCenter(point);
    stringstream imagePath;
    imagePath<< IMG_PATH<<"/" <<"gattling"<< level<<IMG_EXTENSION;
    window->draw_img(imagePath.str(),Rectangle(center.x-45,center.y-45,90,90));
    bullet.draw(window);
}