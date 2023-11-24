#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <cstring>
#include "Sprite.h"

class UI
{
protected:
	char text[100];	//�ؽ�Ʈ
	bool isDisable = false;	//Ȱ������

	SDL_Renderer *UIrenderer;

	SDL_Color defaultColor;
	SDL_Color backgroundColor;	//����
	SDL_Color disableColor;		//��Ȱ��
	SDL_Color overlineColor;	//�ٱ���
	SDL_Rect drawing;		//��ǥ, ũ�⿡ �׸� �簢��

	//�߰��Ұ� : �̹���, �׶��̼�
	Sprite* imageUI = NULL;
	
	//Font
	TTF_Font *font;
	SDL_Color fontColor = { 0,0,0 };
	SDL_Surface* fontSurface;
	SDL_Texture* fontTexture;
	int fontSize = 30;	//��Ʈ ũ��
	SDL_Rect fontRct = { 0,0,0,0 };	//��Ʈ ũ�� �� ��ġ�� ���� �簢��
public:
	UI(SDL_Renderer *getRend) : UIrenderer(getRend) 
	{
		if (TTF_Init() == -1) this->~UI();
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

	//initialize Image

	//font controll
	void SetFontColor(SDL_Color color);
	void SetFontColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a = 0xff);
	void SetFontStyle(const char *style, int size);	//��Ʈ ��Ÿ�ϰ� ũ�� ����
	void SetFontDistance(int x, int y, int w, int h);	//�簢�� ���� ��Ʈ���� ����

	void SetUIText(const char* str);
	virtual void DrawUI(int x, int y, int w, int h);
	void DrawText(int x, int y, int w, int h);

	void SetDisableUI(bool b) { isDisable = b; }

protected:
	void DrawingUI(SDL_Rect rect);	//ȭ�鿡 �׷��� �޼���
private:
	void SetBackgroundImage();
	void SetDisableImage();
};

class Button : public UI
{
protected:
	SDL_Color overMouseColor;	//���콺 ���� �÷����� ��
	SDL_Color clickColor;		//Ŭ���Ǿ��� ��
	bool isInMouse = false;
	bool isClick = false;
public:
	Button(SDL_Renderer* getRend) : UI(getRend) {}
	~Button() { SDL_DestroyRenderer(UIrenderer); }
	void SetOverMouseColor(SDL_Color color);
	void SetOverMouseColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a = 0xff);
	void SetClickColor(SDL_Color color);
	void SetClickColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a = 0xff);

	virtual bool CheckMouseAction(SDL_Event getButtonCheck);
	bool GetOverMouse() { return isInMouse; }
	bool GetClickMouse() { return isClick; }

	void DrawUI(int x, int y, int w, int h);
};

class Toggle : public Button
{
private:
	bool isToggle = false;

	//checking Icon or bgColor
	SDL_Color checkedColor;

	//�̹��� �ϳ��θ� �Ǻ�
	Sprite* checkedImage;
	Sprite* nonCheckedImage;
public:
	Toggle(SDL_Renderer* getRend) : Button(getRend) {}
	~Toggle() { SDL_DestroyRenderer(UIrenderer); }

	bool GetToggleState() { return isToggle; }	//���� ��� ����

	//������ �� Ȱ�� �Ǵ� ��Ȱ������ ��ȯ
	void SetCheckedColor(SDL_Color color);
	void SetCheckedColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a = 0xff);

	bool CheckMouseAction(SDL_Event getEvent);

	void DrawUI(int x, int y, int l);

private:	//�ϼ� ���Ѱ�
	void SetCheckedImage(Sprite& getSprite);
};

enum BAR_DIRECTION { BAR_HORIZONTAL = 0, BAR_VERTICAL };
class Bar : public UI
{
private:
	int minimum, maximum, nowProgress;

	BAR_DIRECTION direction;
	SDL_Color progressingColor;
	SDL_Rect prog;
public:
	Bar(SDL_Renderer* getRend) : UI(getRend)
	{
		minimum = 0;
		maximum = 100;
		direction = BAR_HORIZONTAL;
	}
	~Bar() { SDL_DestroyRenderer(UIrenderer); }
	void SetMaximum(int i)
	{
		if (minimum >= i) return;
		else maximum = i;
	}
	void SetNowProgress(int i)
	{	//�ּҰ��� �ִ밪 ���̰� �ƴϸ�
		if (minimum > i || maximum < i) return;
		else nowProgress = i;
	}

	int GetNowProgress() { return nowProgress; }
	int GetMaximun() { return maximum; }

	void SetDirection(BAR_DIRECTION dir) { direction = dir; };
	void SetNowProgressColor(SDL_Color color);
	void SetNowProgressColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a = 0xff);

	void DrawUI(int x, int y, int w, int h);
};

class Scroll : public UI
{
	int length = 3;
	int page = 1;
	Button *cursor;
	Button *left, *right;
	BAR_DIRECTION direction;
	SDL_Rect cursorBar;
	SDL_Rect cursorMove;
public:
	Scroll(SDL_Renderer* getRend) : UI(getRend) 
	{ 
		direction = BAR_HORIZONTAL;
		cursor = new Button(getRend);
		left = new Button(getRend);
		right = new Button(getRend);
	}
	~Scroll() 
	{ 
		cursor->~Button();
		left->~Button();
		right->~Button();
		SDL_DestroyRenderer(UIrenderer);
	}

	void SetDirection(BAR_DIRECTION dir) { direction = dir; };
	void CheckCursorButton(SDL_Event e);
	void SetCursorButtonColor(SDL_Color color);
	void SetCursorButtonColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a = 0xff);
	void SetCursorOverColor(SDL_Color color);
	void SetCursorOverColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a = 0xff);
	void SetCursorClickedColor(SDL_Color color);
	void SetCursorClickedColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a = 0xff);

	void DrawUI(int x, int y, int w, int h);
};