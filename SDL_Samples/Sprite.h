#pragma once
#include <SDL.h>

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
	void FrameLoop(int startFrame, int endFrame, int count = 0);	//count동안 start부터 end까지 반복
	void FrameSpin(int startFrame, int endFrame, int count = 0);	//start부터 end까지 돌면서 반복
	void FrameTimeline(int* getFrame, int count = 0);				//getFrame의 길이 만큼 출력하기

	Vector2 GetPosition() const { return centerPos; }
	Vector2 GetLength() const { return length; }
};