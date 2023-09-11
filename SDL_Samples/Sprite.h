#pragma once
#include <SDL.h>

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
	void FrameLoop(int startFrame, int endFrame, int count = 0);	//count���� start���� end���� �ݺ�
	void FrameSpin(int startFrame, int endFrame, int count = 0);	//start���� end���� ���鼭 �ݺ�
	void FrameTimeline(int* getFrame, int count = 0);				//getFrame�� ���� ��ŭ ����ϱ�

	Vector2 GetPosition() const { return centerPos; }
	Vector2 GetLength() const { return length; }
};