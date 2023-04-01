#include "StubbornRunner.hpp"
#include <sstream>
using namespace std;


#define INTERVAL_OF_IMAGES 15
#define IMAGE_EXTENSION ".png"
#define IMAGE_DIRECTORY_ADDRESS "moving/StubbornRunner"
#define UP_IMAGES_DIRECTORY "up"
#define DOWN_IMAGES_DIRECTORY "down"
#define RIGHT_IMAGES_DIRECTORY  "right"
#define ORIGINAL_IMAGE_DIRECTORY "Assets/enemies/stubborn-runner"
#define INITIAL_HEALTH 400
#define SPEED 30
#define MONEY_FOR_KILLING 10
#define TAKE_HEALTH 4

StubbornRunner::StubbornRunner() : Enemy(INITIAL_HEALTH, SPEED, MONEY_FOR_KILLING, TAKE_HEALTH)
{
}
void StubbornRunner::draw(Window *window)
{
    if (xInTerritory(destination))
    {
        if (isMovingDown())
        {
            stringstream imagePath;
            static int downPicNumber = 0;
            static int downFrame = 0;
            downFrame++;
            if (downFrame == INTERVAL_OF_IMAGES)
            {
                downPicNumber++;
                downFrame = 0;
            }
            downPicNumber %= 10;
            imagePath << IMAGE_DIRECTORY_ADDRESS<<"/"<<UP_IMAGES_DIRECTORY<<"/" << downPicNumber << IMAGE_EXTENSION;
            window->draw_img(imagePath.str(), Rectangle((int)point.x - 25, (int)point.y - 31, 50, 62));
        }
        else if (isMovingUp())
        {
            stringstream imagePath;
            static int upPicNumber = 0;
            static int upFrame = 0;
            upFrame++;
            if (upFrame == INTERVAL_OF_IMAGES)
            {
                upPicNumber++;
                upFrame = 0;
            }
            upPicNumber %= 14;
            imagePath << IMAGE_DIRECTORY_ADDRESS<<"/"<<DOWN_IMAGES_DIRECTORY<< "/" << upPicNumber << IMAGE_EXTENSION;
            window->draw_img(imagePath.str(), Rectangle((int)point.x - 25, (int)point.y - 30, 50, 60));
        }
    }
    else if (yIsInTerritory(destination))
    {
        if (isMovingLeft())
        {
            stringstream imagePath;
            static int leftFrame = 0;
            static int leftPicNumber = 0;
            leftFrame++;
            if (leftFrame == INTERVAL_OF_IMAGES)
            {
                leftPicNumber++;
                leftFrame = 0;
            }
            leftPicNumber %= 16;
            imagePath << IMAGE_DIRECTORY_ADDRESS<<"/"<<"left"<<"/" << leftPicNumber << IMAGE_EXTENSION;
            window->draw_img(imagePath.str(), Rectangle((int)point.x - 25, (int)point.y - 25, 50, 50));
        }
        else if (isMovingRight())
        {
            stringstream imagePath;
            static int rightFrame = 0;
            static int rightPicNumber = 0;
            rightFrame++;
            if (rightFrame == INTERVAL_OF_IMAGES)
            {
                rightPicNumber++;
                rightFrame = 0;
            }
            rightPicNumber %= 16;
            imagePath << IMAGE_DIRECTORY_ADDRESS<<"/"<<RIGHT_IMAGES_DIRECTORY<<"/" << rightPicNumber << IMAGE_EXTENSION;
            window->draw_img(imagePath.str(), Rectangle((int)point.x - 25, (int)point.y - 25, 50, 50));
        }
    }
}