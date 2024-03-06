#pragma once
#include <SDL.h>
#include <SDL_image.h>


class Sprite
{
private:
	SDL_Renderer* sprRenderer;
	SDL_Texture* sprTexture;	//��������Ʈ �ؽ���
	SDL_Surface* imageFile;		//�̹��� ���ҽ�

	SDL_Palette *palette;	//�ȷ�Ʈ
	int paletteCount = 1;

	SDL_Rect sprRct;	//���� ������ ��µ� Rect
	SDL_Rect scrnRct;	//���� ȭ�鿡 ��µ� Rect

	Uint32 Color = 0;			//������ �������� �����ϱ� ���� �Ӽ�
	SDL_Point rotatePoint;		//��������Ʈ ȸ���߽���

	float scaleWidth = 1, scaleHeight = 1;	//Ȯ�� ����

	void FindPaletteColor(SDL_Color c);	//�ȷ�Ʈ �ߺ� �˻��
public:
	Sprite(SDL_Renderer* getRenderer, const char* fileName);
	~Sprite();

	void SetSpriteClip(int x, int y, int w, int h);	//�̹��� ������ �Ϻθ� ��Ÿ�� ����
	void SetSpriteClip(SDL_Rect rct) { sprRct = rct; }
	void SetSpriteScale(float w, float h);				//ũ�� ����
	void SetRotatePoint(int x, int y);				//�߽��� ����
	void SetColorHide(SDL_Color setColor);			//����� ����
	void SetColorHide(Uint8 r, Uint8 g, Uint8 b, Uint8 a = 0xff);
	void Drawing(int x, int y, int dir, bool mirror = 0);	//ȭ�鿡 �׸���
	void DrawFill() const;	//��üȭ������ ä���

	//������ �� �ʺ� �� ���� ��ȯ
	int GetImageWidth() const { return imageFile->w; };
	int GetImageHeight() const { return imageFile->h; };
	//��������Ʈ Ŭ���� �� �ʺ� �� ���� ��ȯ
	int GetClipWidth() const { return sprRct.w * scaleWidth; }
	int GetClipHeight() const { return sprRct.h * scaleHeight; }

	void SetColorBlend(Uint8 r, Uint8 g, Uint8 b);	//�ش� �������� ����
	void SetColorBlend(SDL_Color setColor);	
	void SetImageAlpha(Uint8 a);		//��������Ʈ ����

	//�ȷ�Ʈ �ɼ�
	void SetPaletteColor(int idx, SDL_Color c);
	void SetPaletteColor(int idx, Uint8 r, Uint8 g, Uint8 b, Uint8 a = 0xff);
	void SetPaletteDirect(SDL_Palette *pal);
	SDL_Color GetPaletteColor(int idx) { if(idx < paletteCount-1) return palette->colors[idx]; };
	int GetPaletteLength() { return paletteCount-1; }
};