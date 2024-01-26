#include "Graphic.h"

Mask::Mask(SDL_Renderer* rend) : renderer(rend) 
{
	//기본값 설정
	defaultBlend = SDL_BLENDMODE_BLEND;
	bgColor = { 255,255,255,128 };
}
void Mask::SetMaskColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	bgColor.r = r;
	bgColor.g = g;
	bgColor.b = b;
	bgColor.a = a;
}
void Mask::SetMaskColor(SDL_Color c) { bgColor = c; }
void Mask::SetMaskMode(SDL_BlendMode blend) { defaultBlend = blend; }

void Mask::DrawWindowMask(int x, int y, int w, int h)
{
	maskScreen.x = x;
	maskScreen.y = y;
	maskScreen.w = w;
	maskScreen.h = h;
}
void Mask::DrawWindowMask(SDL_Rect rct) { maskScreen = rct; }
void Mask::DrawMask()
{
	SDL_SetRenderDrawColor(renderer, bgColor.r, bgColor.g, bgColor.b, bgColor.a);
	SDL_SetRenderDrawBlendMode(renderer, defaultBlend);
	SDL_RenderFillRect(renderer, &maskScreen);
}
void Mask::DrawFillMask() const { SDL_RenderFillRect(renderer, NULL); }