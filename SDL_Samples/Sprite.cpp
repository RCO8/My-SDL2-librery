#include "Sprite.h"
#include <fstream>
using namespace std;

Sprite::Sprite(SDL_Renderer* getRenderer, const char* fileName)	//스프라이트 불러와서 데이터에 저장
{
	sprRenderer = getRenderer;

	imageFile = SDL_LoadBMP(fileName);	//이미지파일 로드
	if (imageFile == NULL)
	{
		SDL_Log("SDL Load BMP Error : %s\n", SDL_GetError());
		this->~Sprite();
	}

	sprTexture= SDL_CreateTextureFromSurface(sprRenderer, imageFile);	//이미지를 텍스쳐로
	if (sprTexture == NULL)
	{
		SDL_Log("SDL Texture Error : %s\n", SDL_GetError());
		this->~Sprite();
	}

	rotatePoint.x = 0;
	rotatePoint.y = 0;
}

Sprite::~Sprite()
{
	//스프라이트 제거
	SDL_DestroyTexture(sprTexture);
	SDL_FreeSurface(imageFile);
	SDL_DestroyRenderer(sprRenderer);
}

void Sprite::SetRotatePoint(int x, int y)
{
	rotatePoint.x = x;
	rotatePoint.y = y;
}

void Sprite::SetColorHide(Uint8 r, Uint8 g, Uint8 b)
{
	Color = SDL_MapRGB(imageFile->format, r, g, b);	//파일의 색을 Color에 지정
	SDL_SetColorKey(imageFile, SDL_TRUE, Color);	//파일의 배경색으로 지정
	sprTexture = SDL_CreateTextureFromSurface(sprRenderer, imageFile);	//다시 파일을 Renderer로 갱신
}

void Sprite::Drawing(int x, int y, int dir)
{
	sprRct.x = 0;
	sprRct.y = 0;
	sprRct.w = 32;
	sprRct.h = 32;

	scrnRct.x = x;
	scrnRct.y = y;
	scrnRct.w = sprRct.w;
	scrnRct.h = sprRct.h;

	if (dir == 360 || dir == -360) dir = 0;

	/*
	텍스쳐화된 스프라이트를 그린다
	두 매개변수 SDL_Rect가 NULL이면 화면 전체 출력
	*/
	SDL_RenderCopyEx(sprRenderer, sprTexture, &sprRct, &scrnRct, dir, &rotatePoint, SDL_FLIP_NONE);
}

void Sprite::DrawFill()
{
	SDL_RenderCopy(sprRenderer, sprTexture, NULL, NULL);
}