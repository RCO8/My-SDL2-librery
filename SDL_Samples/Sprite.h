#pragma once
#include <fstream>
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
	SDL_Rect spriteClip;	//스프라이트 파일이 여러개가 있을경우 잘라서 저장
	Vector2 startPos;	//스프라이트 그릴때 시작좌표
	Vector2 centerPos;	//스프라이트 중심점
	Vector2 length;		//스프라이트 가로세로 길이
	int frame = 0, maxFrame = 0;	//스프라이트 움직일때 사용하는 프레임
	char filename[30];

	SDL_Texture* spriteTexture;
	SDL_Surface* loadImg;
public:
	Sprite(SDL_Renderer* getRender, const char* fileName);
	~Sprite();
	void AddonSprite();
	void SetCenterPos(int x, int y);
	void SetSpriteLength(int width, int height);
	void DrawSprite(SDL_Renderer* renderer);	//실제로 스프라이트를 출력
	void FrameLoop(int startFrame, int endFrame, int count);	//count동안 start부터 end까지 반복
	void FrameSpin(int startFrame, int endFrame, int count);	//start부터 end까지 돌면서 반복
	void FrameTimeline(int* getFrame);							//getFrame의 길이 만큼 출력하기

	Vector2 GetPosition() const { return centerPos; }
	Vector2 GetLength() const { return length; }
};

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

void Sprite::DrawSprite(SDL_Renderer* renderer)
{
	SDL_Rect rct;
	//rct.w = static_cast<int>(length.x * );
	//rct.h = static_cast<int>(length.y * );
}