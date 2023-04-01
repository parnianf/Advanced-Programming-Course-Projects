#include "GoodReads.hpp"
using namespace std;

int main(int argc, char *argv[])
{

    GoodReads goodReads;
    goodReads.readFiles(argv[1]);
    doCommand(goodReads);
    return 0;
}