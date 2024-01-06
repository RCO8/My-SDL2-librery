#include "Graphic.h"

Gradation::Gradation(SDL_Renderer* getRend) : renderer(getRend)
{
	nowGradientIndex = 2;
	gradientColors[0] = { 0,0,0,255 };
	gradientColors[1] = { 255,255,255,255 };
}

void Gradation::AddGradient(SDL_Color color)
{
	if (nowGradientIndex > maxColorIndex)
	{
		SDL_Log("Too much Gradation Index!!!");
		return;
	}
	gradientColors[nowGradientIndex] = color;
	nowGradientIndex++;
}

void Gradation::RemoveGradient(int idx)
{
	if (idx > nowGradientIndex)
	{
		SDL_Log("Overflow Gradation Index!!!");
		return;
	}
	for (int i = idx; i < nowGradientIndex - 1; i++)
		gradientColors[i] = gradientColors[i + 1];
	nowGradientIndex--;
}
void Gradation::RemoveGradient(SDL_Color color)
{
	int foundIdx, i;
	for (i = 0; i < nowGradientIndex; i++)
	{
		if (&gradientColors[i] == &color)
		{
			foundIdx = i;
			break;
		}
	}
	for (i = foundIdx; i < nowGradientIndex - 1; i++)
		gradientColors[i] = gradientColors[i + 1];
	nowGradientIndex--;
}

void Gradation::SetColorIndex(int idx, SDL_Color color)
{
	if (idx > nowGradientIndex)
	{
		SDL_Log("Overflow Gradation Index!!!");
		return;
	}
	gradientColors[idx] = color;
}

void Gradation::DrawGradation(int x, int y, int w, int h)
{
	gradientRect.x = x;
	gradientRect.y = y;
	gradientRect.w = w;
	gradientRect.h = h;

	Drawing();
}
void Gradation::DrawGradation(SDL_Rect rct)
{
	gradientRect = rct;

	Drawing();
}
void Gradation::Drawing()
{
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

	for (int i = 0; i < 256; i++)
	{
		SDL_SetRenderDrawColor(renderer,
			gradientColors[0].r, gradientColors[0].g,
			gradientColors[0].b, 10);
		SDL_RenderFillRect(renderer, &gradientRect);
	}
}


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