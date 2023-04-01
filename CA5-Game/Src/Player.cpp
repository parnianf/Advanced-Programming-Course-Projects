
#include "Player.hpp"
#include <sstream>
using namespace std;
Player::Player()
{
    health = 20;
    money = 200;
}
int Player::getHearts()
{
    return health;
}

int Player::getMoney()
{
    return money;
}

void Player::decreaseHealth(int health_)
{
    health -= health_;
}

void Player::increaseMoney(int money_)
{
    money += money_;
}

void Player::decreaseMoney(int money_)
{
    money -= money_;
}
void Player::draw(Window *window)
{
    stringstream heart;
    heart << health;
    window->show_text("HEARTS", Point(1295, 78), WHITE, "Assets/OpenSans.ttf", 14);
    window->show_text(heart.str(), Point(1250, 30), WHITE, "Assets/OpenSans.ttf", 30);
    stringstream gold;
    gold << money;
    window->show_text("GOLD", Point(26, 82), WHITE, "Assets/OpenSans.ttf", 14);
    window->show_text(gold.str(), Point(80, 35), WHITE, "Assets/OpenSans.ttf", 30);
}