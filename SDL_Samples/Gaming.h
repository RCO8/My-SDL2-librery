#pragma once
#include "Sprite.h"
#include "Sound.h"
#include "Timer.h"
#include "Joystick.h"
#include <SDL.h>

class Gaming
{
private:
    bool quit = false;
    SDL_Window* window; //SDL â
    SDL_Renderer* renderer; //â�� �׸� ����
    SDL_Surface* surface;
    Timer mTimer;

    Sprite* bgImg;
    Sound* soundEffect;

    Joystick* mJoystick;

    int x = 30;
    int y = 50;
public:
    bool GameInit();    //���� ���۽� �⺻���� ����
    void GameRun();     //���� ������
    void GameOff();     //���� ����
private:
    void CheckKeyPress();	//Ű �� �̺�Ʈ Ȯ��
    void DrawScreen();		//���ȭ�� �׸���
    void PlayAudio();       //�Ҹ� ���
};