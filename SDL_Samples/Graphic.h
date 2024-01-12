#pragma once
#include <SDL.h>

class Gradation
{
private:
	SDL_Renderer* renderer;

	const int maxColorIndex = 10;
	SDL_Color gradientColors[10];
	int nowGradientIndex;

	SDL_Rect gradientRect;
public:
	Gradation(SDL_Renderer* getRend);
	~Gradation() { SDL_DestroyRenderer(renderer); }

	void AddGradient(SDL_Color color);
	void RemoveGradient(int idx);
	void RemoveGradient(SDL_Color color);
	void SetColorIndex(int idx, SDL_Color color);
	void DrawGradation(int x, int y, int w, int h);
	void DrawGradation(SDL_Rect rct);
private:
	void Drawing();	//public의 Draw함수의 공통사용
};

class Mask	//창 색상 효과
{
private:
	SDL_Renderer* renderer;

	SDL_Color bgColor;	//마스킹 색상
	SDL_BlendMode defaultBlend;	//마스킹 모드
	SDL_Rect maskScreen;	//일부분 마스킹할 영역
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
	void DrawMask();	//이거는 설정받은대로 그리는 메서드 Draw~Mask를 호출 받을 때
};

class Polygon
{
private:
	SDL_Renderer* renderer;
	int poly = 3;
	int r;
};