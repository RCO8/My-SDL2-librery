#pragma once
#include <SDL.h>

struct Vector2
{
	int x, y;
};

class Sprite
{
protected:
	SDL_Renderer* sprRenderer;
	SDL_Texture* sprTexture;	//��������Ʈ �ؽ���
	SDL_Surface* imageFile;		//�̹��� ���ҽ�

	SDL_Rect sprRct;	//���� ������ ��µ� Rect
	SDL_Rect scrnRct;	//���� ȭ�鿡 ��µ� Rect

	Uint32 Color = 0;			//������ �������� �����ϱ� ���� �Ӽ�
	SDL_Point rotatePoint;		//��������Ʈ ȸ���߽���
public:
	Sprite(SDL_Renderer* getRenderer, const char* fileName);
	~Sprite();

	void SetSpriteClip(int x, int y, int w, int h);	//�Ϻη� ��Ÿ�� ����
	void SetSpriteScale(int w, int h);				//ũ�� ����
	void SetRotatePoint(int x, int y);				//�߽��� ����
	void SetColorHide(Uint8 r, Uint8 g, Uint8 b);	//����� ����
	void Drawing(int x, int y, int dir, int mirror = 0);			//��������Ʈ �׸���
	void DrawFill() const;	//��üȭ������ ä���

	int GetImageWidth() const { return imageFile->w; };
	int GetImageHeight() const { return imageFile->h; };
};