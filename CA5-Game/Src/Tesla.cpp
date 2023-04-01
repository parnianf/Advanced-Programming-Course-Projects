#include"Tesla.hpp"
#include"rsdl.hpp"
#include"Functions.hpp"
#include<sstream>
using namespace std;


#define IMG_PATH "Assets/towers"
#define IMG_EXTENSION ".png"
#define SHOOTING_DEALY 1500
#define BIULD_COST 120
#define DAMAGE 700
#define UPGRADE_COST 100
#define UPGRADE_DAMAGE 1000



Tesla::Tesla(int level,Point point) : Tower(DAMAGE,SHOOTING_DEALY,BIULD_COST,UPGRADE_COST,UPGRADE_DAMAGE,level,point){

}

void Tesla::damageEnemy(){
    if(bullet.hasEnemy()){
        if(bullet.isHitTheEnemy()){
            bullet.damageEnemy(damage);
            bullet.fadeIfDead();
        }
    }
    
}


void Tesla::upgradeTower(){

    if(level < 3){
        damage += upgrade.increasedDamage;
        level++;
    }
       
}


void Tesla::draw(Window* window) { 
    Point center = getTheCenter(point);
    stringstream imagePath;
    imagePath<<IMG_PATH <<"/"<<"tesla" << level<<IMG_EXTENSION;
    window->draw_img(imagePath.str(),Rectangle(center.x-45,center.y-45,90,90));
    bullet.draw(window);

}
