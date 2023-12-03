#pragma once
#include <SDL.h>
#include "Sprite.h"
#include "Timer.h"
#include "UI.h"
#include "Sound.h"

class Gaming
{
private:
    bool quit = false;
    SDL_Window* window; //SDL â
    SDL_Renderer* renderer; //â�� �׸� ����
    SDL_Event event;    //�Է� �̺�Ʈ

    Timer mTimer;
    Bar* barInterface;
    UI* Text;

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