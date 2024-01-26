#pragma once
#include <SDL.h>

class Mask	//â ���� ȿ��
{
private:
	SDL_Renderer* renderer;

	SDL_Color bgColor;	//����ŷ ����
	SDL_BlendMode defaultBlend;	//����ŷ ���
	SDL_Rect maskScreen;	//�Ϻκ� ����ŷ�� ����
public:
	Mask(SDL_Renderer* rend);
	~Mask() { SDL_DestroyRenderer(renderer); }
	void SetMaskColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
	void SetMaskColor(SDL_Color c);
	void SetMaskMode(SDL_BlendMode blend);

	void DrawWindowMask(int x, int y, int w, int h);
	void DrawWindowMask(SDL_Rect rct);
	void DrawFillMask() const;
private:
	void DrawMask();	//�̰Ŵ� ����������� �׸��� �޼��� Draw~Mask�� ȣ�� ���� ��
};

class Polygon
{
private:
	SDL_Renderer* renderer;
	int poly = 3;
	int r;
};

class Rect
{
	
};