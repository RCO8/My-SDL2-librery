#include "UI.h"

void UI::SetBackgroundColor(SDL_Color color)
{ backgroundColor = color; }
void UI::SetBackgroundColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	backgroundColor.r = r;
	backgroundColor.g = g;
	backgroundColor.b = b;
	backgroundColor.a = a;
}
void UI::SetOverlineColor(SDL_Color color)
{ overlineColor = color; }
void UI::SetOverlineColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	overlineColor.r = r;
	overlineColor.g = g;
	overlineColor.b = b;
	overlineColor.a = a;
}
void UI::SetDisableColor(SDL_Color color)
{ disableColor = color; }
void UI::SetDisableColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	disableColor.r = r;
	disableColor.g = g;
	disableColor.b = b;
	disableColor.a = a;
}
void UI::SetFontColor(SDL_Color color)
{ fontColor = color; }
void UI::SetFontColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	fontColor.r = r;
	fontColor.g = g;
	fontColor.b = b;
	fontColor.a = a;
}
void UI::SetUIText(char* str) 
{
	*text = *str; 
	fontSurface = TTF_RenderText_Blended(font, text, fontColor);
	fontTexture = SDL_CreateTextureFromSurface(UIrenderer, fontSurface);
}
void UI::DrawUI(int x, int y, int w, int h)
{
	drawing.x = x;
	drawing.y = y;
	drawing.w = w;
	drawing.h = h;

	//Checking Disable
	defaultColor = isDisable ? disableColor : backgroundColor;
	//background color
	SDL_SetRenderDrawColor(UIrenderer,
		defaultColor.r, defaultColor.g,
		defaultColor.b, defaultColor.a);
	SDL_RenderFillRect(UIrenderer, &drawing);
	//overline color
	SDL_SetRenderDrawColor(UIrenderer,
		overlineColor.r, overlineColor.g,
		overlineColor.b, overlineColor.a);
	SDL_RenderDrawRect(UIrenderer, &drawing);

	//drawing text
	SDL_RenderCopy(UIrenderer, fontTexture, NULL, &drawing);
}

//Button
void Button::SetOverMouseColor(SDL_Color color)
{
	overMouseColor = color;
}
void Button::SetOverMouseColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	overMouseColor.r = r;
	overMouseColor.g = g;
	overMouseColor.b = b;
	overMouseColor.a = a;
}
void Button::SetClickColor(SDL_Color color)
{
	clickColor = color;
}
void Button::SetClickColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	clickColor.r = r;
	clickColor.g = g;
	clickColor.b = b;
	clickColor.a = a;
}
void Button::DrawUI(int x, int y, int w, int h)
{
	drawing.x = x;
	drawing.y = y;
	drawing.w = w;
	drawing.h = h;

	//checking Button Action
	if (isDisable) defaultColor = disableColor;
	else
	{
		if (isInMouse)
			defaultColor = isClick ? clickColor : overMouseColor;
		else
			defaultColor = backgroundColor;
	}

	//background color
	SDL_SetRenderDrawColor(UIrenderer,
		defaultColor.r, defaultColor.g,
		defaultColor.b, defaultColor.a);
	SDL_RenderFillRect(UIrenderer, &drawing);
	//overline color
	SDL_SetRenderDrawColor(UIrenderer,
		overlineColor.r, overlineColor.g,
		overlineColor.b, overlineColor.a);
	SDL_RenderDrawRect(UIrenderer, &drawing);
}
void Button::OverMouseAction(int mouseX, int mouseY)
{
	isInMouse = ((drawing.x <= mouseX && drawing.x + drawing.w >= mouseX)
		&& (drawing.y <= mouseY && drawing.y + drawing.h >= mouseY)) ? true : false;
}
void Button::ClickMouseAction(SDL_EventType getButtonCheck)
{
	if (isInMouse)
	{
		if (getButtonCheck == SDL_MOUSEBUTTONDOWN)
		{
			SDL_Log("Clicked");
			isClick = true;
		}
		else
		{
			SDL_Log("Not Click");
			isClick = false;
		}
	}
	
	//isClick이 참이 되었다면 실행할 메서드를 실행
}