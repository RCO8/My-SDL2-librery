#pragma once
#include <iostream>
using namespace std;
#include <SDL.h>
#include <SDL_image.h>

struct Vector2
{
	int x, y;
};

class Sprite
{
private:
	Vector2 startPos;	//스프라이트 그릴때 시작좌표
	Vector2 centerPos;	//스프라이트 중심점
	int width, height;
	int frame = 0, maxFrame = 0;	//스프라이트 움직일때 사용하는 프레임
	char filename[30];

	SDL_Texture* realScreen;
	SDL_Surface* loadBMP;
public:
	Sprite();
	void AddonSprite();
	void SetCenterPos(int x, int y);
	void FrameLoop(int startFrame, int endFrame, int count);	//count동안 start부터 end까지 반복
	void FrameSpin(int startFrame, int endFrame, int count);	//start부터 end까지 돌면서 반복
	void FrameTimeline(int* getFrame);

	void LoadImage();       //이미지 불러오기

	Vector2 GetPosition() const { return centerPos; }
};

Sprite::Sprite()
{
	IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
	//처음에 스프라이트 파일을 불러오고 프레임 수를 1씩 증가
	frame++;
	maxFrame++;
}

void Sprite::LoadImage()
{
	loadBMP = SDL_LoadBMP("img.bmp");
	if (loadBMP == NULL)
	{
		cout << "BMP not exist : " << SDL_GetError() << endl;
		SDL_DestroyTexture(realScreen);
		return;
	}
	//realScreen = SDL_CreateTextureFromSurface(renderer, loadBMP);  //화면에 나타낼 텍스쳐 BMP를 배경화면으로
	//if (loadBMP != NULL) SDL_RenderCopy(renderer, realScreen, NULL, NULL);   //텍스쳐 그리기
}

void Sprite::SetCenterPos(int x, int y)
{
	centerPos.x = x;
	centerPos.y = y;
}

void Sprite::AddonSprite()
{

}

void Sprite::FrameLoop(int startFrame, int endFrame, int count)
{
	int tmp = 0;
	
	while (tmp < count)
	{
		//프레임 반복
		for (int idx = startFrame; idx = endFrame; idx++)
		{
			//출력 스프라이트
		}

		if(count > 0)	tmp++;	//무한반복
	}
}

void Sprite::FrameSpin(int startFrame, int endFrame, int count)
{
	int tmp = 0;
	int idx;

	while (tmp < count)
	{
		for (idx = startFrame; idx < endFrame; idx++)
		{

		}
		for (idx = endFrame; idx > startFrame; idx--)
		{

		}
		if (count > 0) tmp++;
	}
}

void Sprite::FrameTimeline(int* getFrame)
{
	//getFrame의 인덱스 수만큼 출력
	int frameLength = sizeof(getFrame) / sizeof(int);
}