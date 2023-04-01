#include "Functions.hpp"
#include <vector>
#include <sstream>
using namespace std;

vector<FPoint> pointCoordinates(vector<vector<int>> coordinates)
{

    vector<FPoint> pointCoordinates;
    for (int i = 0; i < coordinates.size(); i++)
    {
        FPoint point;
        point.x = coordinates[i][0] * 60 + 151;
        point.y = coordinates[i][1] * 60 + 206;
        pointCoordinates.push_back(point);
    }
    return pointCoordinates;
}

vector<vector<int>> getInputEnemies()
{

    int theRunner, stubbornRunner, superTrooper, scramble;
    string line;
    stringstream enemiesNumber(line);
    vector<vector<int>> enemies;
    while (cin >> theRunner >> stubbornRunner >> superTrooper >> scramble)
    {
        vector<int> e;
        e.push_back(theRunner);
        e.push_back(stubbornRunner);
        e.push_back(superTrooper);
        e.push_back(scramble);
        enemies.push_back(e);
    }
    return enemies;
}

vector<vector<int>> getInputCoordinates()
{
    vector<vector<int>> coordinates;
    int x, y;
    string line;
    getline(cin, line);
    stringstream inputCoordinates(line);
    while (inputCoordinates >> x >> y)
    {
        vector<int> coordinate;
        coordinate.push_back(x);
        coordinate.push_back(y);
        coordinates.push_back(coordinate);
    }
    return coordinates;
}

FPoint getNextPoint(vector<FPoint> coordinates, FPoint currentPoint)
{

    for (int i = 0; i < coordinates.size(); i++)
    {
        if (isReachedDstWithError(coordinates[i], currentPoint))
        {
            return coordinates[i + 1];
        }
    }
}
bool isReachedDstWithError(FPoint p1, FPoint p2)
{
    float deltaX = p1.x - p2.x;
    float deltaY = p1.y - p2.y;
    if (pow(1, 2) >= ((powf(deltaX, 2) + (powf(deltaY, 2)))))
    {
        return true;
    }
    return false;
}

bool isDstInSameColumn(FPoint point, FPoint dstPoint)
{
    return (point.x == dstPoint.x);
}

bool isDstInSameLine(FPoint point, FPoint dstPoint)
{
    return (point.y == dstPoint.y);
}

Point getTheCenter(Point point)
{
    Point centerPoint;
    centerPoint.x = (((point.x - 121) / 60) * 60) + 30 + 121;
    centerPoint.y = (((point.y - 176) / 60) * 60) + 30 + 176;
    return centerPoint;
}
