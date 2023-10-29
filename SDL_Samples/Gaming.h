#pragma once
#include <SDL.h>
#include "Sprite.h"
#include "Timer.h"
#include "Joystick.h"
#include "UI.h"

class Gaming
{
private:
    bool quit = false;
    SDL_Window* window; //SDL â
    SDL_Renderer* renderer; //â�� �׸� ����
    SDL_Event event;    //�Է� �̺�Ʈ

    Timer mTimer;
    Sprite* bgImg;
    UI* userInterface;
    Button* buttonInterface;

    int x = 30;
    int y = 50;
    bool isClick = false;
public:
    bool GameInit();    //���� ���۽� �⺻���� ����
    void GameRun();     //���� ������
    void GameOff();     //���� ����
private:
    void CheckKeyPress();	//Ű �̺�Ʈ Ȯ��
    void DrawScreen();		//���ȭ�� �׸���
    void UpdateData();      //���� ������ �� ���� ����
};