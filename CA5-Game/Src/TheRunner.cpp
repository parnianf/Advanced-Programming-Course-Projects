#include "TheRunner.hpp"
#include <sstream>
using namespace std;


#define INTERVAL_OF_IMAGES 15
#define IMAGE_EXTENSION ".png"
#define IMAGE_DIRECTORY_ADDRESS "moving/TheRunner"
#define UP_IMAGES_DIRECTORY "up"
#define DOWN_IMAGES_DIRECTORY "down"
#define RIGHT_IMAGES_DIRECTORY  "right"
#define ORIGINAL_IMAGE_DIRECTORY "Assets/enemies/runner"
#define SPEED 50
#define INITIAL_HEALTH 250
#define MONEY_FOR_KILLING 6
#define TAKE_HEALTH 1

TheRunner::TheRunner() : Enemy(INITIAL_HEALTH, SPEED, MONEY_FOR_KILLING, TAKE_HEALTH)
{
}

void TheRunner::draw(Window *window)
{
    stringstream imagePath;

    if (xInTerritory(destination))
    {
        if (isMovingDown())
        {
            static int downPicNumber = 0;
            static int downFrame = 0;
            downFrame++;
            if (downFrame == INTERVAL_OF_IMAGES)
            {
                downPicNumber++;
                downFrame = 0;
            }
            downPicNumber %= 8;
            imagePath << IMAGE_DIRECTORY_ADDRESS<<"/"<<UP_IMAGES_DIRECTORY<<"/" << downPicNumber << IMAGE_EXTENSION;
            window->draw_img(imagePath.str(), Rectangle((int)point.x - 17, (int)point.y - 26, 34, 52));
        }
        else if (isMovingUp())
        {
            static int upPicNumber = 0;
            static int upFrame = 0;
            upFrame++;
            if (upFrame == INTERVAL_OF_IMAGES)
            {
                upPicNumber++;
                upFrame = 0;
            }
            upPicNumber %= 11;
            imagePath << IMAGE_DIRECTORY_ADDRESS<<"/"<<DOWN_IMAGES_DIRECTORY<<"/" << upPicNumber << IMAGE_EXTENSION;
            window->draw_img(imagePath.str(), Rectangle((int)point.x - 17, (int)point.y - 26, 34, 52));
        }
    }
    else if (yIsInTerritory(destination))
    {
        if (isMovingLeft())
        {static int leftFrame = 0;
            static int leftPicNumber = 0;
            leftFrame++;
            if (leftFrame == INTERVAL_OF_IMAGES)
            {
                leftPicNumber++;
                leftFrame = 0;
            }
            leftPicNumber %= 9;
            imagePath << IMAGE_DIRECTORY_ADDRESS<<"/"<<"left"<<"/" << leftPicNumber << IMAGE_EXTENSION;
            window->draw_img(imagePath.str(), Rectangle((int)point.x - 17, (int)point.y - 26, 34, 52));
        }
        else if (isMovingRight())
        {
            static int rightFrame = 0;
            static int rightPicNumber = 0;
            rightFrame++;
            if (rightFrame == INTERVAL_OF_IMAGES)
            {
                rightPicNumber++;
                rightFrame = 0;
            }
            rightPicNumber %= 9;
            imagePath << IMAGE_DIRECTORY_ADDRESS<<"/"<<RIGHT_IMAGES_DIRECTORY<<"/" << rightPicNumber << IMAGE_EXTENSION;
            window->draw_img(imagePath.str(), Rectangle((int)point.x - 17, (int)point.y - 26, 34, 52));
        }
    }
}