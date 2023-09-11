#pragma once
#include <iostream>
using namespace std;
#include <SDL2/SDL.h>

class Gaming
{
private:
    bool quit = false;
    SDL_Window* window;
    SDL_Renderer* renderer;

public:
    bool GameInit();
    void GameRun();
    void GameOff();
private:
    void CheckKeyPress();	//키 및 이벤트 확인
    void DrawScreen();		//배경화면 그리기
};