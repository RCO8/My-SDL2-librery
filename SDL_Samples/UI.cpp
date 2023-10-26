#include "UI.h"

void UI::SetBackgroundColor(SDL_Color color)
{
	backgroundColor = color;
}
void UI::SetUIText(char* str)
{
	*text = *str;
}
void UI::DrawUI(Vector2D startPos, Vector2D endPos)
{

}

//Button
void Button::SetOverMouseColor(SDL_Color color)
{
	overMouseColor = color;
}
void Button::SetClickColor(SDL_Color color)
{
	clickColor = color;
}
void Button::SetDisableColor(SDL_Color color)
{
	disableColor = color;
}
void Button::SetEnable(bool b)
{
	enable = b;
	defaultColor = enable ? backgroundColor : disableColor;
}
void Button::OverMouseAction()
{
	if (enable)
	{
		// if(사각형 이내에 올려져 있으면)
		defaultColor = overMouseColor;
	}
}
void Button::ClickMouseAction()
{
	if (enable)
	{
		//사각형 이내에 클릭되었으면
		defaultColor = clickColor;
	}
}
void Button::DrawUI(Vector2D startPos, Vector2D endPos)
{

}

//Toggle
