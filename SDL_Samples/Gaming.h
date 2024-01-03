#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "Joystick.h"
#include "Sprite.h"
#include "Timer.h"
#include "UI.h"
#include "Sound.h"
#include "Graphic.h"

class Gaming
{
private:
    bool quit = false;
    SDL_Window* window; //SDL â
    SDL_Renderer* renderer; //â�� �׸� ����
    SDL_Event event;    //�Է� �̺�Ʈ

    GamePad* gPad;
public:
    bool GameInit();    //���� ���۽� �⺻���� ����
    void GameRun();     //���� ������
    void GameOff();     //���� ����
private:
    void CheckKeyPress();	//Ű �̺�Ʈ Ȯ��
    void DrawScreen();		//���ȭ�� �׸���
    void UpdateData();      //���� ������ �� ���� ����
};

class Icon
{
private:
    SDL_Surface* icon;
public:
    Icon(SDL_Window *w, const char* iconName)
    {
        icon = IMG_Load(iconName);
        if (w == NULL || icon == NULL)
        {
            SDL_Log("Icon Load Error : %s", SDL_GetError());
            this->~Icon();
        }
        SDL_SetWindowIcon(w, icon);
    }
    ~Icon() { SDL_FreeSurface(icon); }
};