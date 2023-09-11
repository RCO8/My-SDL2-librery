#pragma once

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
	int frame, maxFrame;	//스프라이트 움직일때 사용하는 프레임
	char filename[30];
public:
	Sprite();
	void AddonSprite();
	void SetCenterPos(int x, int y);
	void FrameLoop(int startFrame, int endFrame, int count);	//count동안 start부터 end까지 반복
	void FrameSpin(int startFrame, int endFrame, int count);	//start부터 end까지 돌면서 반복
	void FrameTimeline(int* getFrame);

	Vector2 GetPosition() const { return centerPos; }
};

Sprite::Sprite()
{
	//처음에 스프라이트 파일을 불러오고 프레임 수를 1씩 증가
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