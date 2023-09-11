#pragma once
#include <SDL.h>

class Gaming
{
private:
    bool quit = false;
    SDL_Window* window; //SDL â
    SDL_Renderer* renderer; //â�� �׸� ����

public:
    bool GameInit();
    void GameRun();
    void GameOff();
private:
    void CheckKeyPress();	//Ű �� �̺�Ʈ Ȯ��
    void DrawScreen();		//���ȭ�� �׸���
};