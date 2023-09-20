#pragma once
#include <SDL.h>

class Joystick
{
private:
	SDL_Joystick* myJoystick;           //연결된 조이스틱과 통신
	const int joystickFixAxis = 256;    //스틱 미입력시 256이 지정되버리는것을 방지
public:
	Joystick(int index = 0);
	~Joystick();
	void CheckJoystickEvent();
};