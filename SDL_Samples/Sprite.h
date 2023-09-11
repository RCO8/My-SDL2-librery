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
	SDL_Rect spriteClip;	//��������Ʈ ������ �������� ������� �߶� ����
	Vector2 startPos;	//��������Ʈ �׸��� ������ǥ
	Vector2 centerPos;	//��������Ʈ �߽���
	Vector2 length;		//��������Ʈ ���μ��� ����
	int frame = 0, maxFrame = 0;	//��������Ʈ �����϶� ����ϴ� ������
	char filename[30];

	SDL_Texture* spriteTexture;
	SDL_Surface* loadImg;
public:
	Sprite(SDL_Renderer* getRender, const char* fileName);
	~Sprite();
	void AddonSprite();
	void SetCenterPos(int x, int y);
	void SetSpriteLength(int width, int height);
	void DrawSprite(SDL_Renderer* renderer);	//������ ��������Ʈ�� ���
	void FrameLoop(int startFrame, int endFrame, int count);	//count���� start���� end���� �ݺ�
	void FrameSpin(int startFrame, int endFrame, int count);	//start���� end���� ���鼭 �ݺ�
	void FrameTimeline(int* getFrame);							//getFrame�� ���� ��ŭ ����ϱ�

	Vector2 GetPosition() const { return centerPos; }
	Vector2 GetLength() const { return length; }
};

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

void Sprite::DrawSprite(SDL_Renderer* renderer)
{
	SDL_Rect rct;
	//rct.w = static_cast<int>(length.x * );
	//rct.h = static_cast<int>(length.y * );
}