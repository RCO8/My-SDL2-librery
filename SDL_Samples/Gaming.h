#pragma once
#include <iostream>
using namespace std;
#include <SDL2/SDL.h>

class Gaming
{
private:
    bool quit = false;
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Surface* loadBMP;

    SDL_Texture* realScreen;
public:
    bool GameInit();
    void GameRun();
    void GameOff();
private:
    void CheckKeyPress();	//Ű �� �̺�Ʈ Ȯ��
    void DrawScreen();		//���ȭ�� �׸���
    void LoadImage();       //�̹��� �ҷ�����
};