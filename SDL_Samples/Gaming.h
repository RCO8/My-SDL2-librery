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
    Sprite* greenRichard;
    Bar* barInterface;
    Sound* soundEffect;
    Music* soundMusic;

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