#pragma once
#include <SDL.h>

struct Vector2
{
	int x, y;
};

class Sprite
{
private:
	SDL_Renderer* sprRenderer;
	SDL_Texture* sprTexture;	//��������Ʈ �ؽ���
	SDL_Surface* imageBMP;	//�̹��� ���ҽ�
	Uint32 Color;	//���� �����ϰ�
public:
	Sprite(SDL_Renderer* getRenderer, const char* fileName);
	~Sprite();

	void SetColorHide(Uint8 r, Uint8 g, Uint8 b);	//����� ����

	void Drawing(int x, int y, int dir);
};
