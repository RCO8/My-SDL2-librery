#pragma once
#include <SDL.h>
#include <SDL_image.h>

class Sprite
{
private:
	SDL_Renderer* sprRenderer;
	SDL_Texture* sprTexture;	//��������Ʈ �ؽ���
	SDL_Surface* imageFile;		//�̹��� ���ҽ�

	SDL_Rect sprRct;	//���� ������ ��µ� Rect
	SDL_Rect scrnRct;	//���� ȭ�鿡 ��µ� Rect

	Uint32 Color = 0;			//������ �������� �����ϱ� ���� �Ӽ�
	SDL_Point rotatePoint;		//��������Ʈ ȸ���߽���

	int scaleWidth = 1, scaleHeight = 1;	//Ȯ�� ����
public:
	Sprite(SDL_Renderer* getRenderer, const char* fileName);
	~Sprite();

	void SetSpriteClip(int x, int y, int w, int h);	//�̹��� ������ �Ϻθ� ��Ÿ�� ����
	void SetSpriteScale(int w, int h);				//ũ�� ����
	void SetRotatePoint(int x, int y);				//�߽��� ����
	void SetColorHide(SDL_Color setColor);			//����� ����
	void Drawing(int x, int y, int dir, int mirror = 0);	//ȭ�鿡 �׸���
	void DrawFill() const;	//��üȭ������ ä���

	//������ �� �ʺ� �� ���� ��ȯ
	int GetImageWidth() const { return imageFile->w; };
	int GetImageHeight() const { return imageFile->h; };
	//��������Ʈ Ŭ���� �� �ʺ� �� ���� ��ȯ
	int GetClipWidth() const { return sprRct.w * scaleWidth; }
	int GetClipHeight() const { return sprRct.h * scaleHeight; }

	void SetColorBlend(SDL_Color setColor);	//�ش� �������� ����
	void SetImageAlpha(Uint8 a);		//��������Ʈ ����
											/*���⼭ Ȯ�� �� �ʿ��� ���*/

	//�÷� �ȷ�Ʈ ���� (�ȼ��� ���� �����ϸ� �ٸ������� ��ȯ)
	//���, ����
	void SetImageGrey();	//�̹��� ���ȭ
	void SetImageNegative();	//�̹��� ������
};