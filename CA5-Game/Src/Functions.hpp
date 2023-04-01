#ifndef FUNCTIONS_H
#define FUNCTIONS_H "FUNCTIONS_H"
#include "FPoint.hpp"
#include "rsdl.hpp"
#include <vector>

class FieldRunners;
Point getTheCenter(Point point);
std::vector<FPoint> pointCoordinates(std::vector<std::vector<int>> coordinates);
std::vector<std::vector<int>> getInputEnemies();
std::vector<std::vector<int>> getInputCoordinates();
FPoint getNextPoint(std::vector<FPoint> coordinates, FPoint currentPoint);
Point getTheCenter(Point point);
FPoint getNextPoint(std::vector<FPoint> coordinates, FPoint currentPoint);
bool isDstInSameColumn(FPoint point, FPoint dstPoint);
bool isDstInSameLine(FPoint point, FPoint dstPoint);
bool isReachedDstWithError(FPoint p1, FPoint p2);
#endif
