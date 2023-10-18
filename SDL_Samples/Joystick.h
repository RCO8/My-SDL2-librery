#pragma once
#include <SDL.h>

const int maxJoystickIndex = 8;	//최대 조이스틱 연결 수

class Joystick
{
private:
	SDL_Joystick* myJoystick[8];           //연결된 조이스틱과 통신
	int numOfJoysticks;
public:
	Joystick();
	~Joystick();
	void CheckJoystickEvent();
	void SetTurbo();	//터보 설정
	//끊겨졌을때와 다시 연결했을때
};