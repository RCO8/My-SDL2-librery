#pragma once
#include <SDL.h>
#include "Sprite.h"
#include "Sound.h"
#include "Timer.h"
#include "Joystick.h"

class Gaming
{
private:
    //SDL을 실행을 하기 위한 중요한 사항들
    bool quit = false;
    SDL_Window* window; //SDL 창
    SDL_Renderer* renderer; //창에 그릴 렌더
    SDL_Surface* surface;
    SDL_Event event;    //입력 이벤트

    //추가적인 사항들
    //Timer mTimer;
    Sprite* bgImg;
    Sound* soundEffect;
    Joystick* mJoystick;

    int x = 30;
    int y = 50;
    bool isClick = false;
public:
    bool GameInit();    //게임 시작시 기본사항 정의
    void GameRun();     //게임 진행중
    void GameOff();     //게임 종료
private:
    void CheckInputEvent();	//키 및 이벤트 확인
    void DrawScreen();		//배경화면 그리기
    void PlayAudio();       //소리 재생
};