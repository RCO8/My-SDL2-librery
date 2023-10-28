#include "UI.h"

void UI::SetBackgroundColor(SDL_Color color)
{
	backgroundColor = color;
}
void UI::SetBackgroundColor(Uint8 r, Uint8 g, Uint8 b)
{
	backgroundColor.r = r;
	backgroundColor.g = g;
	backgroundColor.b = b;
}
void UI::SetOverlineColor(SDL_Color color)
{
	overlineColor = color;
}
void UI::SetOverlineColor(Uint8 r, Uint8 g, Uint8 b)
{
	overlineColor.r;
	overlineColor.g;
	overlineColor.b;
}
void UI::SetDisableColor(SDL_Color color)
{
	disableColor = color;
}
void UI::SetDisableColor(Uint8 r, Uint8 g, Uint8 b)
{
	disableColor.r = r;
	disableColor.g = g;
	disableColor.b = b;
}
void UI::SetUIText(char* str) { *text = *str; }
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
}

//Button
void Button::SetOverMouseColor(SDL_Color color)
{
	overMouseColor = color;
}
void Button::SetOverMouseColor(Uint8 r, Uint8 g, Uint8 b)
{
	overMouseColor.r = r;
	overMouseColor.g = g;
	overMouseColor.b = b;
}
void Button::SetClickColor(SDL_Color color)
{
	clickColor = color;
}
void Button::SetClickColor(Uint8 r, Uint8 g, Uint8 b)
{
	clickColor.r = r;
	clickColor.g = g;
	clickColor.b = b;
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
void Button::ClickMouseAction(int getAction)
{
	isClick = isInMouse && getAction ? true : false;
	//isClick이 참이 되었다면 실행할 메서드를 실행
}