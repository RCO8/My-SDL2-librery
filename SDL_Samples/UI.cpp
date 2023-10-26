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
		// if(�簢�� �̳��� �÷��� ������)
		defaultColor = overMouseColor;
	}
}
void Button::ClickMouseAction()
{
	if (enable)
	{
		//�簢�� �̳��� Ŭ���Ǿ�����
		defaultColor = clickColor;
	}
}
void Button::DrawUI(Vector2D startPos, Vector2D endPos)
{

}

//Toggle
