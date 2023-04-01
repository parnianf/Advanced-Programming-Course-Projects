
#include"Bullet.hpp"
Bullet::Bullet(Point originPoint_){
    originPoint.x = originPoint_.x;
    originPoint.y = originPoint_.y;
    point.x = originPoint_.x;
    point.y = originPoint_.y;
    enemy = NULL;
}

FPoint Bullet::getPoint() { return point; }

void Bullet::draw(Window* window){
    Point center((int)point.x,(int)point.y);
    window->fill_circle(center,5,RED);
}
void Bullet::setEnemy(Enemy* enemy_){
    enemy = enemy_;
}

bool Bullet::isHitTheEnemy(){
    if(isHit){
        return true;
    }
    return false;
}

FPoint Bullet::getEnemysPoint(){ return enemy->getPoint(); }


void Bullet::move(){

    float deltaX = enemy->getPoint().x - point.x;
    float deltaY = enemy->getPoint().y - point.y;
    float distance = sqrt(pow(deltaX,2) + pow(deltaY,2));
    float sin = deltaX / distance;
    float cos = deltaY / distance;
    point.x += (200 * 10/1000) * sin;
    point.y += (200 * 10/1000) * cos;

}

void Bullet::reset(){
    point.x = originPoint.x;
    point.y = originPoint.y;
}

void Bullet::deletLastEnemy(){
    enemy = NULL;
}

bool Bullet::hasEnemy(){
    if(enemy == NULL){
        return false;
    }
    return true;
}
void Bullet::fadeIfDead(){
    enemy->isEnemyDead();
}

bool Bullet::isInTerritory(){
    int deltaX = abs(enemy->getPoint().x - point.x);
    int deltaY = abs(enemy->getPoint().y - point.y); 
    if(pow(1,2) >= (pow(deltaX,2) + (pow(deltaY,2)))) {
        isHit = true;
        return true;
    }
    isHit =false;
    return false;
}

void Bullet::damageEnemy(float damage){
    enemy->decreaseHealth(damage);
}
float Bullet::getEnemySpeed(){return enemy->getSpeed(); }


