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

    Joystick* joystick;
    GamePad* console;
    Timer mTimer;
    Sprite* blueBobby;
    Sprite* greenRichard;
    UI* userInterface;
    Bar* barInterface;
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