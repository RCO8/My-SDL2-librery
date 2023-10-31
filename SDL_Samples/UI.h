#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <cstring>

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
	SDL_Rect drawing;		//좌표, 크기에 그릴 사각형

	//추가할것 : 이미지, 그라데이션
	//Font
	/*수정사항
	* 글꼴스타일, 정렬, 채우기 및 맞추기, 색상 지정
	*/
	TTF_Font *font;
	SDL_Color fontColor = { 0,0,0 };
	SDL_Surface* fontSurface;
	SDL_Texture* fontTexture;
	int fontSize = 30;	//폰트 크기
	SDL_Rect fontRct;	//폰트 크기 및 위치를 맞출 사각형
public:
	UI(SDL_Renderer *getRend) : UIrenderer(getRend) 
	{
		if (TTF_Init() == -1)
			this->~UI();
		font = TTF_OpenFont("HanSantteutDotum-Bold.ttf", fontSize);
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

	//font controll
	void SetFontColor(SDL_Color color);
	void SetFontColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a = 0xff);
	void SetFontStyle(const char *style, int size);	//폰트 스타일과 크기 지정
	void SetFontDistance(int x, int y, int w, int h);	//사각형 내의 폰트와의 간격

	void SetUIText(const char* str);
	virtual void DrawUI(int x, int y, int w, int h);

	void SetDisableUI(bool b) { isDisable = b; }
};

class Button : public UI
{
private:
	SDL_Color overMouseColor;	//마우스 위에 올려놓을 때
	SDL_Color clickColor;		//클릭되었을 때

	bool isInMouse = false;
	bool isClick = false;

public:

	Button(SDL_Renderer* getRend) : UI(getRend) {}
	~Button() { SDL_DestroyRenderer(UIrenderer); }
	void SetOverMouseColor(SDL_Color color);
	void SetOverMouseColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a = 0xff);
	void SetClickColor(SDL_Color color);
	void SetClickColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a = 0xff);

	void OverMouseAction(int mouseX, int mouseY);
	bool ClickMouseAction(SDL_Event getButtonCheck);

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