#pragma once
#include <SDL.h>

class UI
{
protected:
	char* text;	//텍스트
	bool isDisable = false;	//활성상태

	SDL_Renderer *UIrenderer;

	SDL_Color defaultColor;
	SDL_Color backgroundColor;	//배경색
	SDL_Color disableColor;		//비활성
	SDL_Color overlineColor;	//바깥선

	SDL_Texture *UItexture;
	SDL_Rect drawing;
public:
	UI(SDL_Renderer *getRend) : UIrenderer(getRend) {}
	~UI() { SDL_DestroyRenderer(UIrenderer); }
	
	//Setting properties color
	void SetBackgroundColor(SDL_Color color);
	void SetBackgroundColor(Uint8 r, Uint8 g, Uint8 b);
	void SetOverlineColor(SDL_Color color);
	void SetOverlineColor(Uint8 r, Uint8 g, Uint8 b);
	void SetDisableColor(SDL_Color color);
	void SetDisableColor(Uint8 r, Uint8 g, Uint8 b);
	void SetUIText(char* str);
	virtual void DrawUI(int x, int y, int w, int h);

	void SetDisableUI(bool b) { isDisable = b; }
};

class Text : UI
{
public:
	char* getString() const { return text; }
};
class Button : public UI
{
private:
	SDL_Color overMouseColor;	//마우스 위에 올려놓을 때
	SDL_Color clickColor;		//클릭되었을 때

	bool isClick = false;
	bool isInMouse = false;

public:
	Button(SDL_Renderer* getRend) : UI(getRend) {}
	void SetOverMouseColor(SDL_Color color);
	void SetOverMouseColor(Uint8 r, Uint8 g, Uint8 b);
	void SetClickColor(SDL_Color color);
	void SetClickColor(Uint8 r, Uint8 g, Uint8 b);

	void OverMouseAction(int mouseX, int mouseY);
	void ClickMouseAction(int getAction);

	void DrawUI(int x, int y, int w, int h);
};
class Toggle : UI
{
private:
	bool isToggle = false;
	//checking Icon or bgColor
public:
};
class List : UI
{

};
class Bar : UI
{
private:
	//정수와 실수 필요
	SDL_Color foreground;
	float minimum = 0, maximum = 10;
	float nowProgress;
public:
	template <typename T>
	void SetMaximum(T i)
	{
		if (minimum >= i)
			return;
		else
			maximum = i;
	}
	template <typename T>
	void SetNowProgress(T i)
	{
		if (minimum > i || maximum < i)	//최소값보다 작거나 최대값보다 크면
			return;
		else
			nowProgress = i;
	}

	template <typename T>
	T GetNowProgress() const { return nowProgress; }
	template <typename T>
	T GetMaximun() const { return maximum; }
};
class Scroll : UI
{
public:
	static enum Axis { Horizontal = 0, Vertical };
};