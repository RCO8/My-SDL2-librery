#pragma once
#include "Sprite.h"
#include <SDL_image.h>
//���� ��������Ʈ ������� Ȯ�� ����

class SpriteEx : public Sprite
{
public:
	void ImageFileImport(char* filename);
	void ImageFileDestroy();
};

void SpriteEx::ImageFileImport(char* filename)
{
	IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);

	imageFile = IMG_Load(filename);
	if (imageFile == NULL)
	{
		SDL_Log("Set Image File Error : %s\n", SDL_GetError());
		ImageFileDestroy();
	}
	sprTexture = SDL_CreateTextureFromSurface(sprRenderer, imageFile);
	if (sprTexture == NULL)
	{
		SDL_Log("Set Texture Error : %s\n", SDL_GetError());
		ImageFileDestroy();
	}
}

void SpriteEx::ImageFileDestroy()
{
	IMG_Quit();
}