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
	Uint32 Color = 0;	//투명한 배경색으로 설정하기 위한 속성
	SDL_Point rotatePoint;	//스프라이트 회전중심점
public:
	Sprite(SDL_Renderer* getRenderer, const char* fileName);
	~Sprite();

	void SetColorHide(Uint8 r, Uint8 g, Uint8 b);	//투명색 설정

	void Drawing(int x, int y, int dir);	//스프라이트 그리기
};
