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
	SDL_Texture* sprTexture;	//스프라이트 텍스쳐
	SDL_Surface* imageBMP;	//이미지 리소스
	Uint32 Color;	//배경색 투명하게
public:
	Sprite(SDL_Renderer* getRenderer, const char* fileName);
	~Sprite();

	void SetColorHide(Uint8 r, Uint8 g, Uint8 b);	//투명색 설정

	void Drawing(int x, int y, int dir);
};
