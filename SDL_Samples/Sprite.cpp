#include "Sprite.h"
#include <SDL_image.h>
#include <fstream>
using namespace std;

Sprite::Sprite(SDL_Renderer* getRender, const char* fileName)	//스프라이트 불러와서 데이터에 저장
{
	IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);

	//파일에 데이터가 있으면 불러오고 없으면 새로 만들기
	
	if (fileName == NULL)
		return;

	loadImg = IMG_Load(fileName);
	if (loadImg == NULL)
		return;

	spriteTexture = SDL_CreateTextureFromSurface(getRender, loadImg);	//이미지를 화면에 그릴 함수

	//처음에 스프라이트 파일을 불러오고 프레임 수를 1씩 증가
	frame++;
	maxFrame++;
}

Sprite::~Sprite()
{
	//스프라이트 제거
	SDL_DestroyTexture(spriteTexture);
	SDL_FreeSurface(loadImg);
}

void Sprite::SetCenterPos(int x, int y)
{
	centerPos.x = x;
	centerPos.y = y;
}

void Sprite::SetSpriteLength(int width, int height)
{
	length.x = width;
	length.y = height;
}

void Sprite::AddonSprite()
{

}

void Sprite::FrameLoop(int startFrame, int endFrame, int count = 0)
{
	int tmp = 0;

	if (startFrame > maxFrame || endFrame > maxFrame || startFrame > endFrame)
	{
		SDL_Log("Set Frame Error!!\n");
		return;
	}

	while (tmp < count)
	{
		//프레임 반복
		for (int idx = startFrame; idx = endFrame; idx++)
		{
			//출력 스프라이트
		}

		if (count > 0)	tmp++;	//무한반복
	}
}

void Sprite::FrameSpin(int startFrame, int endFrame, int count = 0)
{
	int tmp = 0;
	int idx;

	if (startFrame > maxFrame || endFrame > maxFrame || startFrame > endFrame)
	{
		SDL_Log("Set Frame Error!!\n");
		return;
	}

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

void Sprite::FrameTimeline(int* getFrame, int count = 0)
{
	int tmp = 0;
	int frameLength = sizeof(getFrame) / sizeof(int);	//getFrame의 인덱스 수만큼 출력

	while (tmp < count)
	{
		for (int idx = 0; idx < frameLength; idx++)
		{

		}
		if(count > 0) tmp++;
	}
}

void Sprite::DrawSprite(SDL_Renderer* renderer)
{
	SDL_Rect rct;
	//rct.w = static_cast<int>(length.x * );
	//rct.h = static_cast<int>(length.y * );
}