#pragma once
#include <SDL.h>

class UI
{
protected:
	char* text;	//�ؽ�Ʈ
	bool isDisable = false;	//Ȱ������

	SDL_Renderer *UIrenderer;

	SDL_Color defaultColor;
	SDL_Color backgroundColor;	//����
	SDL_Color disableColor;		//��Ȱ��
	SDL_Color overlineColor;	//�ٱ���

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
	SDL_Color overMouseColor;	//���콺 ���� �÷����� ��
	SDL_Color clickColor;		//Ŭ���Ǿ��� ��

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
	//������ �Ǽ� �ʿ�
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
		if (minimum > i || maximum < i)	//�ּҰ����� �۰ų� �ִ밪���� ũ��
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