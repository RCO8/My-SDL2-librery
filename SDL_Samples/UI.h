#pragma once
#include <SDL.h>
#include <SDL_ttf.h>

struct Vector2D {
	int x, y;
};

class UI
{
protected:
	char* text;
	TTF_Font *font;

	SDL_Color defaultColor;
	SDL_Color backgroundColor;
	SDL_Color overMouseColor;	//마우스 위에 올려놓을 때
	SDL_Color disableColor;		//비활성
public:
	void SetBackgroundColor(SDL_Color color);
	void SetUIText(char* str);
	virtual void DrawUI(Vector2D startPos, Vector2D endPos);
};

class Text : UI
{
public:
	char* getString() const { return text; }
};
class Button : UI
{
private:
	bool isClick = false;
	bool enable = true;

	SDL_Color clickColor;		//클릭되었을 때
public:
	void SetOverMouseColor(SDL_Color color);
	void SetClickColor(SDL_Color color);
	void SetDisableColor(SDL_Color color);
	void SetEnable(bool b);

	void OverMouseAction();
	void ClickMouseAction();

	void DrawUI(Vector2D startPos, Vector2D endPos);
};
class Toggle : UI
{
private:
	bool isToggle = false;
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