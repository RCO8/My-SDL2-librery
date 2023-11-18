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
{ 
	fontColor = color;
	fontSurface = TTF_RenderText_Blended(font, text, fontColor);
	fontTexture = SDL_CreateTextureFromSurface(UIrenderer, fontSurface);
}
void UI::SetFontColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	fontColor.r = r;
	fontColor.g = g;
	fontColor.b = b;
	fontColor.a = a;
	fontSurface = TTF_RenderText_Blended(font, text, fontColor);
	fontTexture = SDL_CreateTextureFromSurface(UIrenderer, fontSurface);
}
void UI::SetFontStyle(const char* style, int size)
{
	fontSize = size;
	font = TTF_OpenFont(style, fontSize);
}
void UI::SetFontDistance(int left, int top, int right, int bottom)
{
	fontRct.x = left;
	fontRct.y = top;
	fontRct.w = right;
	fontRct.h = bottom;
}
void UI::SetUIText(const char* str) 
{
	int getStrLength = SDL_strlen(str);
	for(int i=0;i<getStrLength;i++)
		text[i] = str[i];
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
	DrawingUI(drawing);
	DrawText(drawing.x, drawing.y, drawing.w, drawing.h);
}
void UI::DrawText(int x, int y, int w, int h)
{
	drawing.x = x;
	drawing.y = y;
	drawing.w = w;
	drawing.h = h;

	//drawing text
	drawing.x += fontRct.x;
	drawing.y += fontRct.y;
	drawing.w -= fontRct.w + fontRct.x;
	drawing.h -= fontRct.h + fontRct.y;
	SDL_RenderCopy(UIrenderer, fontTexture, NULL, &drawing);	//폰트를 사각형 안에 그리기
}
void UI::DrawingUI(SDL_Rect rect)
{
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
		defaultColor = backgroundColor;
		if (isInMouse)
			defaultColor = isClick ? clickColor : overMouseColor;
	}
	DrawingUI(drawing);
	DrawText(drawing.x, drawing.y, drawing.w, drawing.h);
}
void Button::OverMouseAction(int mouseX, int mouseY)
{
	isInMouse = ((drawing.x <= mouseX && drawing.x + drawing.w >= mouseX)
		&& (drawing.y <= mouseY && drawing.y + drawing.h >= mouseY)) ? true : false;
}
bool Button::ClickMouseAction(SDL_Event getButtonCheck)
{
	if (isInMouse)
	{
		//SDL_Log("Button Click");
		isClick = getButtonCheck.button.state;
	}
	return isClick;
}

//Toggle
void Toggle::SetCheckedColor(SDL_Color color)
{ checkedColor = color; }
void Toggle::SetCheckedColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	checkedColor.r = r;
	checkedColor.g = g;
	checkedColor.b = b;
	checkedColor.a = a;
}
bool Toggle::ClickMouseAction(SDL_Event getButtonCheck)
{
	isClick = getButtonCheck.button.state;
	if (isInMouse)
		if (!isToggle)
		{
			isToggle = true;
			SDL_Log("Toggle Checked");
		}
		else
		{
			isToggle = false;
			SDL_Log("Toggle Unchecked");
		}

	return isToggle;
}
void Toggle::DrawUI(int x, int y, int l)
{
	drawing.x = x;
	drawing.y = y;
	drawing.w = l;
	drawing.h = l;

	//checking Button Action
	if (isDisable) defaultColor = disableColor;
	else
	{
		if (isInMouse)
			defaultColor = isClick ? clickColor : overMouseColor;
		else
			defaultColor = isToggle ? checkedColor : backgroundColor;
	}

	DrawingUI(drawing);

	//DrawText(drawing.x, drawing.y, drawing.w, drawing.h);
	//drawing text (사각형 밖으로 나오게)
	SDL_Rect textRect = drawing;	//drawing으로 텍스트 위치로 지정하면 마우스를 올릴때 텍스트에 적용되기 때문에 새로운 Rect형 생성하고 복사
	textRect.x += fontRct.x + drawing.x;
	textRect.y += fontRct.y;
	textRect.w -= fontRct.w - drawing.w;
	textRect.h -= fontRct.h;
	SDL_RenderCopy(UIrenderer, fontTexture, NULL, &textRect);	//폰트를 사각형 안에 그리기
}

//Bar
void Bar::SetNowProgressColor(SDL_Color color)
{ progressingColor = color; }
void Bar::SetNowProgressColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	progressingColor.r = r;
	progressingColor.g = g;
	progressingColor.b = b;
	progressingColor.a = a;
}
void Bar::DrawUI(int x, int y, int w, int h)
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

	//progress color
	SDL_SetRenderDrawColor(UIrenderer,
		progressingColor.r, progressingColor.g,
		progressingColor.b, progressingColor.a);
	prog = drawing;
	float percent;
	if (direction == BAR_HORIZONTAL)
	{
		percent = (drawing.w / maximum) * nowProgress;
		prog.w = percent;
	}
	else if (direction == BAR_VERTICAL)
	{
		percent = (drawing.h / maximum) * nowProgress;
		prog.h = percent;
	}
	SDL_RenderFillRect(UIrenderer, &prog);

	//overline color
	SDL_SetRenderDrawColor(UIrenderer,
		overlineColor.r, overlineColor.g,
		overlineColor.b, overlineColor.a);
	SDL_RenderDrawRect(UIrenderer, &drawing);
}

//Scroll
void Scroll::SetLeftButtonColor(SDL_Color color)
{
	left->SetBackgroundColor(color);
	right->SetBackgroundColor(color);
}
void Scroll::DrawUI(int x, int y, int w, int h)
{
	drawing.x = x;
	drawing.y = y;
	drawing.w = w;
	drawing.h = h;

	//Checking Disable
	defaultColor = isDisable ? disableColor : backgroundColor;
	DrawingUI(drawing);

	//버튼 그리기 양쪽 버튼은 UI길이의 5%
}