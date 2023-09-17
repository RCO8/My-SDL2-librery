#pragma once
#include <SDL.h>
#include "Sprite.h"
#include "Sound.h"

class Gaming
{
private:
    bool quit = false;
    SDL_Window* window; //SDL 창
    SDL_Renderer* renderer; //창에 그릴 렌더

    Sprite* bgImg;

    int x = 30;
    int y = 50;

    Sound* soundEffect;

public:
    bool GameInit();    //게임 시작시 기본사항 정의
    void GameRun();     //게임 진행중
    void GameOff();     //게임 종료
private:
    void CheckKeyPress();	//키 및 이벤트 확인
    void DrawScreen();		//배경화면 그리기
    void PlayAudio();       //소리 재생
};