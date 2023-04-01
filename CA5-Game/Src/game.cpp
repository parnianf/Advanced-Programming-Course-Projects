#include <iostream>
#include <vector>
#include "rsdl.hpp"
#include "Functions.hpp"
#include "FieldRunners.hpp"
using namespace std;

#define DELAY_BETWEEN_WAVES 3000
#define GAME_DELAY 10
#define WINDOW_WIDTH 1365
#define WINDOW_HEGHT 1024
int main()
{
    FieldRunners fieldRunners;
    vector<vector<int>> coordinates = getInputCoordinates();
    vector<vector<int>> enemies = getInputEnemies();
    vector<FPoint> pointOfCoordinates = pointCoordinates(coordinates);
    Window *window = new Window(WINDOW_WIDTH, WINDOW_HEGHT, "FieldRunners!!!");
    for (int wave = 0; wave < enemies.size(); wave++)
    {
        int frame = 0;
        fieldRunners.creatEnemies(enemies, wave);
        while (1)
        {
            fieldRunners.updateEvent(window);
            fieldRunners.processGame(pointOfCoordinates, frame);
            fieldRunners.draw(window);
            fieldRunners.winOrLose(window,wave,enemies.size());
            if(fieldRunners.isWaveFinished()){
                break;
            }
            delay(GAME_DELAY);
            frame++;
        }
        delay(DELAY_BETWEEN_WAVES);
    }
}
