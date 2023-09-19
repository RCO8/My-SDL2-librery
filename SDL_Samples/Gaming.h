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
    Sound* soundEffect;

public:
    bool GameInit();    //���� ���۽� �⺻���� ����
    void GameRun();     //���� ������
    void GameOff();     //���� ����
private:
    void CheckKeyPress();	//Ű �� �̺�Ʈ Ȯ��
    void DrawScreen();		//���ȭ�� �׸���
    void DrawParticle();    //��ƼŬ �׸���
    void PlayAudio();       //�Ҹ� ���
};