#include "MessageBox.h"

MessageBox::MessageBox(SDL_Window* window)
{
	mbd.window = window;
	mbd.title = "";
	mbd.message = "";
	mbd.flags = SDL_MESSAGEBOX_INFORMATION;
}
void MessageBox::SetTitle(const char* str)
{ mbd.title = str; }
void MessageBox::SetMessage(const char* str)
{ mbd.message = str; }
void MessageBox::AddonButton(const char* str)
{
	buttonsProps.text = str;
	buttonsProps.buttonid = buttonIndex;
	buttonsProps.flags = buttonIndex;
	mbd.buttons = &buttonsProps;
	mbd.numbuttons = buttonsProps.buttonid;
	buttonIndex++;
}
void MessageBox::SetBackgroundColor(SDL_Color color)
{
	colorsProps.colors[SDL_MESSAGEBOX_COLOR_BACKGROUND].r = color.r;
	colorsProps.colors[SDL_MESSAGEBOX_COLOR_BACKGROUND].g = color.g;
	colorsProps.colors[SDL_MESSAGEBOX_COLOR_BACKGROUND].b = color.b;
	mbd.colorScheme = &colorsProps;
}
void MessageBox::SetBackgroundColor(Uint8 r, Uint8 g, Uint8 b)
{
	colorsProps.colors[SDL_MESSAGEBOX_COLOR_BACKGROUND].r = r;
	colorsProps.colors[SDL_MESSAGEBOX_COLOR_BACKGROUND].g = g;
	colorsProps.colors[SDL_MESSAGEBOX_COLOR_BACKGROUND].b = b;
	mbd.colorScheme = &colorsProps;
}
void MessageBox::SetFontColor(SDL_Color color)
{

}
void MessageBox::SetFlag(SDL_MessageBoxFlags flag)
{
	//�޼����ڽ� �ȿ� ������ ǥ��
	mbd.flags = flag;
}
int MessageBox::AlertMessageBox()
{
	SDL_ShowMessageBox(&mbd, &mbd.numbuttons);
	//��ư�� Ŭ���ϸ� ��ư �ε��� ��ȯ
	//SDL_Log("%d", mbd.buttons->buttonid);
	return mbd.buttons->buttonid;
}