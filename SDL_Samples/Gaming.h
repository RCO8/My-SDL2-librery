#pragma once
#include <SDL.h>
#include "Sprite.h"
#include "Sound.h"
#include "Timer.h"
#include "Joystick.h"

class Gaming
{
private:
    bool quit = false;
    SDL_Window* window; //SDL â
    SDL_Renderer* renderer; //â�� �׸� ����
    SDL_Event event;    //�Է� �̺�Ʈ

    //Timer mTimer;
    Sprite* bgImg;
    Sound* soundEffect;
    //Joystick* mJoystick;

    int x = 30;
    int y = 50;
    int dir = 0;
    bool isClick = false;
    bool mirror = false;
public:
    bool GameInit();    //���� ���۽� �⺻���� ����
    void GameRun();     //���� ������
    void GameOff();     //���� ����
private:
    void CheckKeyPress();	//Ű �̺�Ʈ Ȯ��
    void DrawScreen();		//���ȭ�� �׸���
    void UpdateData();      //���� ������ �� ���� ����
};