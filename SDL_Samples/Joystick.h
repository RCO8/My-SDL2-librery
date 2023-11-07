#pragma once
#include <SDL.h>

const int maxJoystickIndex = 8;

//Arcade ver
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

//Console ver
class GamePad
{
private:
	SDL_GameController* gameController;
	char* gamePadName;

	const int maxAxis = 32768;    //Controller Max Axis
	int stickDead;
	float checkBattery;
public:
	GamePad(int index);
	~GamePad();

	char getControllerName() { return *gamePadName; }
	void CheckGamepadEvent(SDL_Event event);

	void SetControllerWave();	//게임 컨트롤러 진동설정
};