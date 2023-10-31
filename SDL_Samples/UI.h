#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <cstring>

class UI
{
protected:
	char* text = nullptr;	//�ؽ�Ʈ
	bool isDisable = false;	//Ȱ������

	SDL_Renderer *UIrenderer;

	SDL_Color defaultColor;
	SDL_Color backgroundColor;	//����
	SDL_Color disableColor;		//��Ȱ��
	SDL_Color overlineColor;	//�ٱ���
	SDL_Rect drawing;		//��ǥ, ũ�⿡ �׸� �簢��

	//�߰��Ұ� : �̹���, �׶��̼�
	//Font
	/*��������
	* �۲ý�Ÿ��, ����, ä��� �� ���߱�, ���� ����
	*/
	TTF_Font *font;
	SDL_Color fontColor = { 0,0,0 };
	SDL_Surface* fontSurface;
	SDL_Texture* fontTexture;
	int fontSize = 30;	//��Ʈ ũ��
	SDL_Rect fontRct;	//��Ʈ ũ�� �� ��ġ�� ���� �簢��
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
	void SetFontStyle(const char *style, int size);	//��Ʈ ��Ÿ�ϰ� ũ�� ����
	void SetFontDistance(int x, int y, int w, int h);	//�簢�� ���� ��Ʈ���� ����

	void SetUIText(const char* str);
	virtual void DrawUI(int x, int y, int w, int h);

	void SetDisableUI(bool b) { isDisable = b; }
};

class Button : public UI
{
private:
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