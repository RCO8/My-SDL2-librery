#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "Joystick.h"
#include "Sprite.h"
#include "Timer.h"
#include "UI.h"
#include "Sound.h"
#include "Graphic.h"

class Gaming
{
private:
    bool quit = false;
    SDL_Window* window; //SDL 창
    SDL_Renderer* renderer; //창에 그릴 렌더
    SDL_Event event;    //입력 이벤트

    GamePad* gPad;
public:
    bool GameInit();    //게임 시작시 기본사항 정의
    void GameRun();     //게임 진행중
    void GameOff();     //게임 종료
private:
    void CheckKeyPress();	//키 이벤트 확인
    void DrawScreen();		//배경화면 그리기
    void UpdateData();      //게임 데이터 및 변수 갱신
};

class Icon
{
private:
    SDL_Surface* icon;
public:
    Icon(SDL_Window *w, const char* iconName)
    {
        icon = IMG_Load(iconName);
        if (w == NULL || icon == NULL)
        {
            SDL_Log("Icon Load Error : %s", SDL_GetError());
            this->~Icon();
        }
        SDL_SetWindowIcon(w, icon);
    }
    ~Icon() { SDL_FreeSurface(icon); }
};