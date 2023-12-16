
#include <iostream>
#include "Gaming.h"

int main(int argc, char* argv[])
{
    Gaming game;
    bool success = game.GameInit();
    game.GameRun();
	game.GameOff();
    return 0;
}