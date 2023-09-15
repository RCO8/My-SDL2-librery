#include "Sprite.h"
#include <fstream>
using namespace std;

Sprite::Sprite(SDL_Renderer* getRenderer, const char* fileName)	//스프라이트 불러와서 데이터에 저장
{
	sprRenderer = getRenderer;

	imageBMP = SDL_LoadBMP(fileName);
	if (imageBMP == NULL)
	{
		SDL_Log("SDL Load BMP Error : %s\n", SDL_GetError());
		this->~Sprite();
	}

	sprTexture= SDL_CreateTextureFromSurface(sprRenderer, imageBMP);	//이미지를 텍스쳐로

	if (sprTexture == NULL)
	{
		SDL_Log("SDL Texture Error : %s\n", SDL_GetError());
		this->~Sprite();
	}
	SDL_SetColorKey(imageBMP, SDL_TRUE, SDL_MapRGB(imageBMP->format, 0, 0, 0));
}

Sprite::~Sprite()
{
	//스프라이트 제거
	SDL_DestroyTexture(sprTexture);
	SDL_FreeSurface(imageBMP);

}

void Sprite::SetColorHide(Uint8 r, Uint8 g, Uint8 b)
{
}

void Sprite::Drawing(int x, int y)
{
	SDL_Rect sprRct;	//파일 내에서 출력될 Rect
	sprRct.x = 0;
	sprRct.y = 0;
	sprRct.w = 32;
	sprRct.h = 32;

	SDL_Rect scrnRct;	//실제 화면에 출력될 Rect
	scrnRct.x = x;
	scrnRct.y = y;
	scrnRct.w = sprRct.w;
	scrnRct.h = sprRct.h;

	/*
	텍스쳐화된 스프라이트를 그린다
	두 매개변수 SDL_Rect가 NULL이면 화면 전체 출력
	파일 내에서 사각형으로 표시될 항목, 실제 좌표에 표시될 항목
	*/
	SDL_RenderCopy(sprRenderer, sprTexture, &sprRct, &scrnRct);
	//SDL_RenderCopyEx(sprRenderer,sprTexture,&sprRct,&scrnRct,)

}