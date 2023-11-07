#pragma once
#include <SDL.h>

const int maxJoystickIndex = 8;

//Arcade ver
//Multi Device in class
class Joystick
{
private:
	SDL_Joystick* myJoystick;           //연결된 조이스틱과 통신
	char* joystickName;					//현재 조이스틱 디바이스 이름

	/* Need checking batter what joystick is wiress*/
	float checkBattery[8];
public:
	Joystick();
	~Joystick();
	void CheckJoystickEvent(SDL_Event event);
};

//Console ver
//Single Device in class
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
	void SetAxisDead(int deadzone);
	void SetControllerWave(int ms,int level = 1);	//Game Controller Wave Level while ms
};