#pragma once
#include <SDL.h>
#include "Sprite.h"
#include "Sound.h"

class Gaming
{
private:
    bool quit = false;
    SDL_Window* window; //SDL â
    SDL_Renderer* renderer; //â�� �׸� ����
    SDL_Surface* surface;

    Sprite* bgImg;
    int x = 30;
    int y = 50;
    int dir = 0;

public:
    bool GameInit();    //���� ���۽� �⺻���� ����
    void GameRun();     //���� ������
    void GameOff();     //���� ����
private:
    void CheckKeyPress();	//Ű �� �̺�Ʈ Ȯ��
    void DrawScreen();		//���ȭ�� �׸���
    void PlayAudio();       //�Ҹ� ���
};