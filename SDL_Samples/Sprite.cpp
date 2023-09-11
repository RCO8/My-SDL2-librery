#include "Sprite.h"
#include <SDL_image.h>
#include <fstream>
using namespace std;

Sprite::Sprite(SDL_Renderer* getRender, const char* fileName)	//��������Ʈ �ҷ��ͼ� �����Ϳ� ����
{
	IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);

	//���Ͽ� �����Ͱ� ������ �ҷ����� ������ ���� �����
	
	if (fileName == NULL)
		return;

	loadImg = IMG_Load(fileName);
	if (loadImg == NULL)
		return;

	spriteTexture = SDL_CreateTextureFromSurface(getRender, loadImg);	//�̹����� ȭ�鿡 �׸� �Լ�

	//ó���� ��������Ʈ ������ �ҷ����� ������ ���� 1�� ����
	frame++;
	maxFrame++;
}

Sprite::~Sprite()
{
	//��������Ʈ ����
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
		//������ �ݺ�
		for (int idx = startFrame; idx = endFrame; idx++)
		{
			//��� ��������Ʈ
		}

		if (count > 0)	tmp++;	//���ѹݺ�
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
	int frameLength = sizeof(getFrame) / sizeof(int);	//getFrame�� �ε��� ����ŭ ���

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