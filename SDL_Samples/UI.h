#pragma once
#include <SDL.h>
#include <SDL_ttf.h>

class UI
{
protected:
	char* text = nullptr;	//텍스트
	bool isDisable = false;	//활성상태

	SDL_Renderer *UIrenderer;

	SDL_Color defaultColor;
	SDL_Color backgroundColor;	//배경색
	SDL_Color disableColor;		//비활성
	SDL_Color overlineColor;	//바깥선
	SDL_Rect drawing;

	//추가할것 : 이미지, 그라데이션, 폰트 스타일
	//Font
	TTF_Font *font;
	SDL_Color fontColor = { 0,0,0 };
	SDL_Surface* fontSurface;
	SDL_Texture* fontTexture;
public:
	UI(SDL_Renderer *getRend) : UIrenderer(getRend) 
	{
		if (TTF_Init() == -1)
			this->~UI();
		font = TTF_OpenFont("HanSantteutDotum-Bold.ttf", 30);
		fontSurface = TTF_RenderText_Blended(font, text, fontColor);
		fontTexture = SDL_CreateTextureFromSurface(UIrenderer, fontSurface);
	}
	~UI()
	{
		TTF_CloseFont(font);
		SDL_DestroyRenderer(UIrenderer);
	}
	
	//Setting properties color
	void SetBackgroundColor(SDL_Color color);
	void SetBackgroundColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a = 0xff);
	void SetOverlineColor(SDL_Color color);
	void SetOverlineColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a = 0xff);
	void SetDisableColor(SDL_Color color);
	void SetDisableColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a = 0xff);

	void SetFontColor(SDL_Color color);
	void SetFontColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a = 0xff);

	void SetUIText(char* str);
	virtual void DrawUI(int x, int y, int w, int h);

	void SetDisableUI(bool b) { isDisable = b; }
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
	~Button() { SDL_DestroyRenderer(UIrenderer); }
	void SetOverMouseColor(SDL_Color color);
	void SetOverMouseColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a = 0xff);
	void SetClickColor(SDL_Color color);
	void SetClickColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a = 0xff);

	void OverMouseAction(int mouseX, int mouseY);
	void ClickMouseAction(SDL_EventType getButtonCheck);

	void DrawUI(int x, int y, int w, int h);
};
class Toggle : public Button
{
private:
	bool isToggle = false;
	//checking Icon or bgColor
	SDL_Color checkedColor;
public:
	Toggle(SDL_Renderer* getRend) : Button(getRend) {}
	~Toggle() { SDL_DestroyRenderer(UIrenderer); }
};
class List : UI
{
private:
	char** ItemText;
	int indexLength = 3;
public:
	void SetIndexLength(int idx);
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