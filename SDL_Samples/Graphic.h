#pragma once
#include <SDL.h>

class Gradation
{
private:
	const int maxColorIndex = 10;
	SDL_Color gradientColors[10];
	int nowGradientIndex;

	SDL_Rect gradientRect;
public:
	Gradation();
	~Gradation();

	void AddGradient(SDL_Color color);
	void RemoveGradient(int idx);
	void RemoveGradient(SDL_Color color);
	void SetColorIndex(int idx, SDL_Color color);
	void DrawGradation();
};

class Polygon
{

};

class Mask
{

};