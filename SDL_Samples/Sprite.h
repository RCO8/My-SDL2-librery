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
	Vector2 startPos;	//��������Ʈ �׸��� ������ǥ
	Vector2 centerPos;	//��������Ʈ �߽���
	int width, height;
	int frame = 0, maxFrame = 0;	//��������Ʈ �����϶� ����ϴ� ������
	char filename[30];

	SDL_Texture* realScreen;
	SDL_Surface* loadBMP;
public:
	Sprite();
	void AddonSprite();
	void SetCenterPos(int x, int y);
	void FrameLoop(int startFrame, int endFrame, int count);	//count���� start���� end���� �ݺ�
	void FrameSpin(int startFrame, int endFrame, int count);	//start���� end���� ���鼭 �ݺ�
	void FrameTimeline(int* getFrame);

	void LoadImage();       //�̹��� �ҷ�����

	Vector2 GetPosition() const { return centerPos; }
};

Sprite::Sprite()
{
	IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
	//ó���� ��������Ʈ ������ �ҷ����� ������ ���� 1�� ����
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
	//realScreen = SDL_CreateTextureFromSurface(renderer, loadBMP);  //ȭ�鿡 ��Ÿ�� �ؽ��� BMP�� ���ȭ������
	//if (loadBMP != NULL) SDL_RenderCopy(renderer, realScreen, NULL, NULL);   //�ؽ��� �׸���
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
		//������ �ݺ�
		for (int idx = startFrame; idx = endFrame; idx++)
		{
			//��� ��������Ʈ
		}

		if(count > 0)	tmp++;	//���ѹݺ�
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
	//getFrame�� �ε��� ����ŭ ���
	int frameLength = sizeof(getFrame) / sizeof(int);
}