#pragma once
#include <SDL.h>

class Gaming
{
private:
    bool quit = false;
    SDL_Window* window; //SDL 창
    SDL_Renderer* renderer; //창에 그릴 렌더

public:
    bool GameInit();
    void GameRun();
    void GameOff();
private:
    void CheckKeyPress();	//키 및 이벤트 확인
    void DrawScreen();		//배경화면 그리기
};