
#include <iostream>
#include "Gaming.h"

int main(int argc, char* argv[])
{
    Gaming game;
    game.GameInit();
    game.GameRun();
	game.GameOff();
    return 0;
}