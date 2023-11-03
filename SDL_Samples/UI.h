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

	void SetDisableUI(bool b) { isDisable = b; }
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

	void OverMouseAction(int mouseX, int mouseY);
	virtual bool ClickMouseAction(SDL_Event getButtonCheck);

	void DrawUI(int x, int y, int w, int h);
};

class Toggle : public Button
{
private:
	bool isToggle = false;
	//checking Icon or bgColor
	SDL_Color checkedColor;

	//�߰��Ұ� 2�� �̹����� �Ǻ�
	//�̹��� �ϳ��θ� �Ǻ�
	Sprite* checkedImage;
	Sprite* nonCheckedImage;
public:
	Toggle(SDL_Renderer* getRend) : Button(getRend) {}
	~Toggle() { SDL_DestroyRenderer(UIrenderer); }

	//������ �� Ȱ�� �Ǵ� ��Ȱ������ ��ȯ
	void ClickToggle();	//Ŭ���� �� ��Ŭ Ȱ��
	void SetToggleOnType();		//��� Ȱ���� ǥ���� ��ũ
	bool GetToggleState() { return isToggle; }	//���� ��� ����

	bool ClickMouseAction(SDL_Event getButtonCheck);

	void DrawUI(int x, int y, int l);

private:	//�ϼ� ���Ѱ�
	void SetCheckedImage(Sprite& getSprite);
	void SetNonCheckedImage(Sprite& getSprite);
};

class Bar : UI
{
private:
	//������ �Ǽ� �ʿ�
	//float minimum = 0, maximum = 10; 
	//float nowProgress;

	/*�Ʒ� ������ ������ �Ǽ��� ����Ұ���
	�ϴ� ����ü�� �����ھ���*/
	union {
		int intValue;
		float floatValue;
	} minimum, maximum, nowProgress;

	SDL_Color progressingColor;
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
		if (minimum > i || maximum < i)	//�ּҰ��� �ִ밪 ���̰� �ƴϸ�
			return;
		else
			nowProgress = i;
	}

	template <typename T>
	T GetNowProgress() const { return nowProgress; }
	template <typename T>
	T GetMaximun() const { return maximum; }

private:
	void DrawUI(int x, int y, int w, int h);
};
class Scroll : UI
{
	int length;
public:
	static enum Type { Horizontal = 0, Vertical };
};
class List : UI
{
private:
	char** ItemText;
	int indexLength = 3;
public:
	void SetIndexLength(int idx);
};