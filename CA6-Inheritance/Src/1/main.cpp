#include "JsonBuilder.hpp"

#include <iostream>

using namespace std;

int main()
{
    JsonBuilder jsonBuilder;
    int x = jsonBuilder.addContainerToObject(0, "parnian", "object");
    int y = jsonBuilder.addContainerToObject(x, "parnian", "object");
    jsonBuilder.addStringToObject(x, "parnian", "salamm");
    jsonBuilder.print(0);
}