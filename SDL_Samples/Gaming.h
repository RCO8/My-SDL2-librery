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
    void CheckKeyPress();	//Ű �� �̺�Ʈ Ȯ��
    void DrawScreen();		//���ȭ�� �׸���
    void LoadImage();       //�̹��� �ҷ�����
    void DrawImage();		//�̹��� �� ��������Ʈ �׸���
    void FreeImage();       //�̹��� �Ҹ��ϱ�

    void DrawParticle();	//��ƼŬ �׸���
    void PlaySound();		//�Ҹ� ���
};