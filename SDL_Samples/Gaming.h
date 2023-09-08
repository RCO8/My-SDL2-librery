#pragma once

class Gaming
{
private:
    bool quit = false;
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Texture* realScreen;
    SDL_Surface* loadBMP;
    
public:
    bool GameInit();
    void GameRun();
    void GameOff();
private:
    void CheckKeyPress();	//키 및 이벤트 확인
    void DrawScreen();		//배경화면 그리기
    void LoadImage();       //이미지 불러오기
    void DrawImage();		//이미지 및 스프라이트 그리기
    void FreeImage();       //이미지 소멸하기

    void DrawParticle();	//파티클 그리기
    void PlaySound();		//소리 재생
};