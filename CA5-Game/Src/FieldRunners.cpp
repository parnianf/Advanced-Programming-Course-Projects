#include "FieldRunners.hpp"
#include "Functions.hpp"
#include "Tower.hpp"
#include "Tesla.hpp"
#include "Glue.hpp"
#include "Gatling.hpp"
#include "Missile.hpp"
#include "Enemy.hpp"
#include "Scramble.hpp"
#include "StubbornRunner.hpp"
#include "SuperTrooper.hpp"
#include "TheRunner.hpp"
#include "Player.hpp"
#include <iostream>
#include <sstream>
#include <map>
#include <ctime>
using namespace std;

#define GATLING_KEY 'g'
#define MISSILE_KEY 'm'
#define TESLA_KEY 't'
#define GLUE_KEY 'l'
#define UPGRADE_KEY 'u'
#define BACKGROUND_IMG_PATH "Assets/background.png"
#define HEART_IMG_PATH "Assets/heart.png"
#define GOLD_IMG_PATH "Assets/gold.png"
#define INTERVAL_BETWEEN_APPEARING_ENEMIES_MS 500
#define DELAY 10
#define YOU_WIN "you win :)"
#define YOU_LOSE "you lose :("
#define SCRAMBLE_TURN_INPUT 3
#define SUPERTROOPER_TURN_INPUT 2
#define THERUNNER_TURN_INPUT 0
#define STUBBERNRUNNER_TURN_INPUT 1


void FieldRunners::createTower(char towerType, Point newTowerPoint)
{
    switch (towerType)
    {
    case GATLING_KEY:
    {
        Gatling *gatling = new Gatling(1, newTowerPoint);
        towers.push_back(gatling);
        player.decreaseMoney(gatling->getBuildCost());
        break;
    }
    case MISSILE_KEY:
    {
        Missile *missile = new Missile(1, newTowerPoint, enemies);
        towers.push_back(missile);
        player.decreaseMoney(missile->getBuildCost());
        break;
    }
    case TESLA_KEY:
    {
        Tesla *tesla = new Tesla(1, newTowerPoint);
        towers.push_back(tesla);
        player.decreaseMoney(tesla->getBuildCost());
        break;
    }
    case GLUE_KEY:
    {
        Glue *glue = new Glue(1, newTowerPoint, enemies);
        towers.push_back(glue);
        player.decreaseMoney(glue->getBuildCost());
        break;
    }
    case UPGRADE_KEY:
    {
        Tower *upgradingTower;
        upgradingTower = findTowerByPoint(newTowerPoint);
        upgradingTower->upgradeTower();
        player.decreaseMoney(upgradingTower->getUpgradingCost());
    }
    break;
    default:
        break;
    }
}

int FieldRunners::getenemiesVectorIndex(Enemy *removedEnemy)
{
    for (int i = 0; i < enemies.size(); i++)
    {
        if (enemies[i] == removedEnemy)
        {
            return i;
        }
    }
    cout << "NOT_FOUND";
}

void FieldRunners::handlePlayer(vector<FPoint> coordinates)
{
    if (enemies.size() != 0)
    {
        handleMoney();
        handleHearts(coordinates);
    }
}



void FieldRunners::handleMoney()
{
    for (int i = 0; i < enemiesInBattle.size(); i++)
    {
        if (enemiesInBattle[i]->isEnemyDead())
        {
            player.increaseMoney(enemiesInBattle[i]->getMoneyForKilling());
            int index = getenemiesVectorIndex(enemiesInBattle[i]);
            enemiesInBattle.erase(enemiesInBattle.begin() + i);
            enemies.erase(enemies.begin() + index);
        }
    }
}

void FieldRunners::handleHearts(vector<FPoint> coordinates)
{
    for (int i = 0; i < enemiesInBattle.size(); i++)
    {
        if (enemiesInBattle[i]->isInEndOfPath(coordinates))
        {
            player.decreaseHealth(enemiesInBattle[i]->getTheTakeHealth());
            int index = getenemiesVectorIndex(enemiesInBattle[i]);
            enemiesInBattle.erase(enemiesInBattle.begin() + i);
            enemies.erase(enemies.begin() + index);
        }
    }
}

void FieldRunners::processGame(vector<FPoint> coordinates, const int frame)
{
    setEnemiesInBattle();
    moveEnemies(coordinates, frame);
    moveBullets(frame);
    handleEnemyHealth();
    handlePlayer(coordinates);
}

void FieldRunners::winOrLose(Window *window, int currentWave, int totalWave)
{
    lose(window, currentWave, totalWave);
    if (isWaveFinished())
    {
        win(window, currentWave, totalWave);
    }
}

void FieldRunners::moveBullets(int frame)
{
    for (int i = 0; i < towers.size(); i++)
    {
        towers[i]->shoot(frame);
    }
}

void FieldRunners::handleEnemyHealth()
{
    for (int i = 0; i < towers.size(); i++)
    {
        towers[i]->damageEnemy();
    }
}

Enemy *FieldRunners::getNearestEnemy(Tower *centerTower)
{
    vector<Enemy *> enemiesInBorder;
    for (int i = 0; i < enemiesInBattle.size(); i++)
    {
        if (centerTower->isInTerritory(enemiesInBattle[i]->getPoint()))
        {
            enemiesInBorder.push_back(enemiesInBattle[i]);
        }
    }
    map<float, Enemy *> distancesAndEnemy;
    for (int i = 0; i < enemiesInBorder.size(); i++)
    {
        float deltaX = centerTower->getPoint().x - enemiesInBorder[i]->getPoint().x;
        float deltaY = centerTower->getPoint().y - enemiesInBorder[i]->getPoint().y;
        float distance = sqrt(pow(deltaX, 2) + pow(deltaY, 2));
        distancesAndEnemy.insert(pair<int, Enemy *>(distance, enemiesInBorder[i]));
    }
    return (distancesAndEnemy.begin()->second);
}

void FieldRunners::setEnemiesInBattle()
{
    for (int i = 0; i < towers.size(); i++)
    {
        if (!towers[i]->hasEnemy())
        {
            towers[i]->setEnemyForBullet(getNearestEnemy(towers[i]));
        }
    }
}

void FieldRunners::draw(Window *window)
{
    window->clear();
    window->draw_img(BACKGROUND_IMG_PATH, NULL_RECT, NULL_RECT);
    window->draw_img(HEART_IMG_PATH, Rectangle(1295, 27, 54, 48));
    window->draw_img(GOLD_IMG_PATH, Rectangle(20, 25, 50, 55));
    for (int j = 0; j < enemiesInBattle.size(); j++)
    {
        enemiesInBattle[j]->draw(window);
    }
    for (int i = 0; i < towers.size(); i++)
    {
        towers[i]->draw(window);
    }
    player.draw(window);
    window->update_screen();
}

Tower *FieldRunners::findTowerByPoint(Point p)
{

    for (int i = 0; i < towers.size(); i++)
    {
        Point point = getTheCenter(p);
        if ((getTheCenter(towers[i]->getPoint()).x == point.x) && (getTheCenter(towers[i]->getPoint()).y == point.y))
        {
            return towers[i];
        }
    }
    return NULL;
}

void FieldRunners::moveEnemies(vector<FPoint> coordinates, const int &frame)
{

    if ((enemiesInBattle.size() < enemies.size()) && !(frame % (INTERVAL_BETWEEN_APPEARING_ENEMIES_MS / DELAY)))
    {
        enemies[enemiesInBattle.size()]->setPoint(coordinates[0]);
        enemies[enemiesInBattle.size()]->setDst(coordinates[1]);
        enemiesInBattle.push_back(enemies[enemiesInBattle.size()]);
    }
    for(int s=0;s<enemiesInBattle.size();s++){
        enemiesInBattle[s]->setP();
    }
    for (int k = 0; k < enemiesInBattle.size(); k++)
    {
        if (enemiesInBattle[k]->isReachedDst())
        {
            enemiesInBattle[k]->setDst(getNextPoint(coordinates, enemiesInBattle[k]->getPoint()));
        }
    }
    for (int j = 0; j < enemiesInBattle.size(); j++)
    {
        if (enemiesInBattle[j]->isInEndOfPath(coordinates))
        {
            enemiesInBattle[j]->fade();
        }
        else {enemiesInBattle[j]->move();}
    }
}

bool FieldRunners::isWaveFinished()
{
    if (enemies.size() == 0)
    {
        return true;
    }
    return false;
}

void FieldRunners::updateEvent(Window *window)
{
    Event event;
    if (window->has_pending_event())
    {
        event = window->poll_for_event();
        static Point point;
        static bool isClicked;
        switch (event.get_type())
        {
        case Event::QUIT:
            exit(0);
            break;
        case Event::LCLICK:
            point = event.get_mouse_position();
            isClicked = true;
            break;
        case Event::KEY_PRESS:
            if (isClicked)
            {
                char towerType = event.get_pressed_key();
                createTower(towerType, point);
                isClicked = false;
            }
            break;
        }
    }
}

void FieldRunners::creatEnemies(vector<vector<int>> enemiesNumber, int wave)
{
    TheRunner *theRunner;
    StubbornRunner *stubbornRunner;
    SuperTrooper *superTrooper;
    Scramble *scramble;
    vector<Enemy *> allEnemies;
    for (int i = 0; i < enemiesNumber[wave][THERUNNER_TURN_INPUT]; i++)
    {
        theRunner = new TheRunner();
        theRunner->setHeartInWave(wave);
        allEnemies.push_back(theRunner);
    }
    for (int i = 0; i < enemiesNumber[wave][STUBBERNRUNNER_TURN_INPUT]; i++)
    {
        stubbornRunner = new StubbornRunner();
        stubbornRunner->setHeartInWave(wave);
        allEnemies.push_back(stubbornRunner);
    }
    for (int i = 0; i < enemiesNumber[wave][SUPERTROOPER_TURN_INPUT]; i++)
    {
        superTrooper = new SuperTrooper();
        superTrooper->setHeartInWave(wave);
        allEnemies.push_back(superTrooper);
    }
    for (int i = 0; i < enemiesNumber[wave][SCRAMBLE_TURN_INPUT]; i++)
    {
        scramble = new Scramble();
        scramble->setHeartInWave(wave);
        allEnemies.push_back(scramble);
    }
    setEnemies(allEnemies);
}

void FieldRunners::setEnemies(vector<Enemy *> allEnemies)
{
    srand(time(0));
    int nemiesNumber = allEnemies.size();
    while (nemiesNumber != enemies.size())
    {
        int size = allEnemies.size();
        int randomIndex = rand() % size;
        enemies.push_back(allEnemies[randomIndex]);
        allEnemies.erase(allEnemies.begin() + randomIndex);
    }
}

void FieldRunners::lose(Window *window, int currentWave, int totalWave)
{
    if (player.getHearts() <= 0)
    {
        stringstream youLose;
        youLose << YOU_LOSE;
        window->show_text(youLose.str(), Point(400, 400), RED, "Assets/OpenSans.ttf", 120);
        window->update_screen();
        delay(3000);
        exit(0);
    }
}

void FieldRunners::win(Window *window, int currentWave, int totalWave)
{
    currentWave++;
    if ((player.getHearts() > 0) && (totalWave == currentWave) && (enemiesInBattle.size() == enemies.size()))
    {
        stringstream youWin;
        youWin << YOU_WIN;
        window->show_text(youWin.str(), Point(400, 400), RED, "Assets/OpenSans.ttf", 120);
        window->update_screen();
        delay(3000);
        exit(0);
    }
}
