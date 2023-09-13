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
	SDL_Texture* sprTexture;	//
	SDL_Surface* imageBMP;	//�̹��� ���ҽ�
	Uint32 Color;
public:
	Sprite(SDL_Renderer* getRenderer, const char* fileName);
	~Sprite();

	void SetColorHide(Uint8 r, Uint8 g, Uint8 b);	//����� ����

	void Drawing();
};
