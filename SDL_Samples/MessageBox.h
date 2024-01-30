#pragma once
#include <SDL.h>

class MessageBox
{
private:
	SDL_MessageBoxData mbd;
	SDL_MessageBoxButtonData buttonsProps;
	SDL_MessageBoxColorScheme colorsProps;

	int buttonIndex = 1;
public:
	MessageBox(SDL_Window* window);
	void SetTitle(const char* str);
	void SetMessage(const char* str);
	void AddonButton(const char* str);
	void RemoveButton();
	void SetBackgroundColor(SDL_Color color);
	void SetBackgroundColor(Uint8 r, Uint8 g, Uint8 b);
	void SetFontColor(SDL_Color color);
	void SetFlag(SDL_MessageBoxFlags flag);
	int AlertMessageBox();
};