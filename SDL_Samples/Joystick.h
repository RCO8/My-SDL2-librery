#pragma once
#include <SDL.h>

const int maxJoystickIndex = 8;

class Joystick
{
private:
	SDL_Joystick* myJoystick;           //연결된 조이스틱과 통신
	char* joystickName;					//현재 조이스틱 디바이스 이름

	/*만약 조이스틱이 무선이라면 배터리 체크 필요*/
	float checkBattery[8];
public:
	Joystick();
	~Joystick();
	void CheckJoystickEvent(SDL_Event event);
};