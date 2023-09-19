#pragma once
#include <SDL.h>

struct Vector2
{
	int x, y;
};

class Sprite
{
protected:
	SDL_Renderer* sprRenderer;
	SDL_Texture* sprTexture;	//스프라이트 텍스쳐
	SDL_Surface* imageFile;		//이미지 리소스

	SDL_Rect sprRct;	//파일 내에서 출력될 Rect
	SDL_Rect scrnRct;	//실제 화면에 출력될 Rect

	Uint32 Color = 0;			//투명한 배경색으로 설정하기 위한 속성
	SDL_Point rotatePoint;		//스프라이트 회전중심점
public:
	Sprite(SDL_Renderer* getRenderer, const char* fileName);
	~Sprite();

	void SetRotatePoint(int x, int y);				//중심점 지정
	void SetColorHide(Uint8 r, Uint8 g, Uint8 b);	//투명색 설정
	void Drawing(int x, int y, int dir);			//스프라이트 그리기
	void DrawFill();	//전체화면으로 채우기
};