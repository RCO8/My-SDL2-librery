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
bool Button::CheckMouseAction(SDL_Event getEvent)
{
	isInMouse = ((drawing.x <= getEvent.motion.x && drawing.x + drawing.w >= getEvent.motion.x)
		&& (drawing.y <= getEvent.motion.y && drawing.y + drawing.h >= getEvent.motion.y)) ? true : false;
	if (isInMouse)
	{
		//SDL_Log("Button Click");
		isClick = getEvent.button.state;
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
bool Toggle::CheckMouseAction(SDL_Event getEvent)
{
	isInMouse = ((drawing.x <= getEvent.motion.x && drawing.x + drawing.w >= getEvent.motion.x)
		&& (drawing.y <= getEvent.motion.y && drawing.y + drawing.h >= getEvent.motion.y)) ? true : false;
	isClick = getEvent.button.state;
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
void Scroll::CheckCursorButton(SDL_Event e)
{
	if (left->CheckMouseAction(e) && page > 1) page--;
	if (right->CheckMouseAction(e) && page < length) page++;
}
void Scroll::SetCursorButtonColor(SDL_Color color)
{ 
	cursor->SetBackgroundColor(color);
	left->SetBackgroundColor(color);
	right->SetBackgroundColor(color);
}
void Scroll::SetCursorButtonColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{ 
	cursor->SetBackgroundColor(r, g, b, a);
	left->SetBackgroundColor(r, g, b, a);
	right->SetBackgroundColor(r, g, b, a);
}
void Scroll::SetCursorOverColor(SDL_Color color)
{ 
	cursor->SetOverMouseColor(color);
	left->SetOverMouseColor(color);
	right->SetOverMouseColor(color);
}
void Scroll::SetCursorOverColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{ 
	cursor->SetOverMouseColor(r, g, b, a);
	left->SetOverMouseColor(r, g, b, a);
	right->SetOverMouseColor(r, g, b, a);
}
void Scroll::SetCursorClickedColor(SDL_Color color)
{ 
	cursor->SetClickColor(color);
	left->SetClickColor(color);
	right->SetClickColor(color);
}
void Scroll::SetCursorClickedColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	cursor->SetClickColor(r, g, b, a);
	left->SetClickColor(r, g, b, a);
	right->SetClickColor(r, g, b, a);
}
void Scroll::DrawUI(int x, int y, int w, int h)
{
	drawing.x = x;
	drawing.y = y;
	drawing.w = w;
	drawing.h = h;

	cursorBar = drawing;

	//Checking Disable
	defaultColor = isDisable ? disableColor : backgroundColor;
	DrawingUI(drawing);

	cursorBar.x = drawing.x + (page - 1) * drawing.w / length;
	cursorBar.y = drawing.y + (page - 1) * drawing.h / length;
	cursorBar.w = drawing.w / length;
	cursorBar.h = drawing.h / length;

	//버튼 그리기 양쪽 버튼은 UI길이의 5%
	if (direction == BAR_HORIZONTAL)
	{
		left->DrawUI(drawing.x - drawing.h, drawing.y, drawing.h, drawing.h);
		cursor->DrawUI(cursorBar.x, drawing.y, cursorBar.w, drawing.h);
		right->DrawUI(drawing.x + drawing.w, drawing.y, drawing.h, drawing.h);
	}
	else if (direction == BAR_VERTICAL)
	{
		left->DrawUI(drawing.x, drawing.y - drawing.w, drawing.w, drawing.w);
		cursor->DrawUI(drawing.x, cursorBar.y, drawing.w, cursorBar.h);
		right->DrawUI(drawing.x, drawing.y + drawing.h, drawing.w, drawing.w);
	}
}