#include <iostream>
#include "Gaming.h"

enum Edition { Arcade, Console };
int main(int argc, char* argv[])
{
    Gaming game;
    game.GameInit();
    game.GameRun();
    game.GameOff();
    return 0;
}