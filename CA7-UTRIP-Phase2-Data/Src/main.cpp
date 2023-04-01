#include"Utrip.hpp"
#include"CVSReader.hpp"
#include"ConsoleHandler.hpp"

int main(int argc, char *argv[]){
    Utrip utrip(argv[1],argv[2]);
    ConsoleHandler consoleHandler(&utrip);
    consoleHandler.processCommand(); 
}

