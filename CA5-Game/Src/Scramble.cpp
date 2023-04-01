#include "Scramble.hpp"
#include "rsdl.hpp"
#include <sstream>
using namespace std;

#define INTERVAL_OF_IMAGES 15
#define IMAGE_EXTENSION ".png"
#define IMAGE_DIRECTORY_ADDRESS "moving/Scramble"
#define UP_IMAGES_DIRECTORY "up"
#define DOWN_IMAGES_DIRECTORY "down"
#define RIGHT_IMAGES_DIRECTORY  "right"
#define ORIGINAL_IMAGE_DIRECTORY "Assets/enemies/scrambler"
#define INITIAL_HEALTH 100
#define SPEED 90
#define MONEY_FOR_KILLING 4
#define TAKE_HEALTH 2

Scramble::Scramble() : Enemy(INITIAL_HEALTH, SPEED, MONEY_FOR_KILLING, TAKE_HEALTH)
{
}

void Scramble::draw(Window *window)
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
            downPicNumber %= 3;
            imagePath << IMAGE_DIRECTORY_ADDRESS<<"/"<<UP_IMAGES_DIRECTORY<<"/" << downPicNumber << IMAGE_EXTENSION;
            window->draw_img(imagePath.str(), Rectangle((int)point.x - 21, (int)point.y - 32, 42, 63));
        }
        if (isMovingUp())
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
            upPicNumber %= 4;
            imagePath <<IMAGE_DIRECTORY_ADDRESS<<"/"<<DOWN_IMAGES_DIRECTORY<<"/" << upPicNumber << IMAGE_EXTENSION;
            window->draw_img(imagePath.str(), Rectangle((int)point.x - 21, (int)point.y - 33, 42, 67));
        }
    }
    if (yIsInTerritory(destination))
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
            leftPicNumber %= 4;
            imagePath << IMAGE_DIRECTORY_ADDRESS<<"/"<<"left"<<"/" << leftPicNumber <<IMAGE_EXTENSION;
            window->draw_img(imagePath.str(), Rectangle((int)point.x - 41, (int)point.y - 24, 83, 48));
        }
        if (isMovingRight())
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
            rightPicNumber %= 4;
            imagePath << IMAGE_DIRECTORY_ADDRESS<<"/"<<RIGHT_IMAGES_DIRECTORY<<"/" << rightPicNumber <<IMAGE_EXTENSION;
            window->draw_img(imagePath.str(), Rectangle((int)point.x - 41, (int)point.y - 24, 83, 48));
        }
    }
}