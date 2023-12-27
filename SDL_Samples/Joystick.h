#pragma once
#include <SDL.h>

const int maxJoystickIndex = 8;

//Arcade ver
//Multi Device in class
class Joystick
{
private:
	SDL_Joystick* myJoystick;           //����� ���̽�ƽ�� ���
	char* joystickName;					//���� ���̽�ƽ ����̽� �̸�

	/* Need checking batter what joystick is wiress*/
	float checkBattery[8];

	//�� �Ӽ����� Gaming���� Ŭ������ ��ȣ�ۿ��� �ϱ� ���ؼ� ������ ��ȯ
	int AxisX[8], AxisY[8];
	int HatSwitches[8];
	bool Buttons[8][12];
public:
	Joystick();
	~Joystick();
	void CheckJoystickEvent(SDL_Event event);
	//���� ����̽����� ������ ���� �Ű� ��ȯ
	int GetAxisX(int idx) { return AxisX[idx]; }
	int GetAxisY(int idx) { return AxisY[idx]; }
	int GetHatSwitches(int idx) { return HatSwitches[idx]; }
	bool GetButtons(int idx, int btn) { return Buttons[idx][btn]; }
};

//Console ver
//Single Device in class
class GamePad
{
private:
	SDL_GameController* gameController;
	char* gamePadName;

	const int maxAxis = 32768;    //Controller Max Axis
	int stickDead = 10000;
	float checkBattery;
	
	//�� ���� ��ƽ�� �������� �� �������� �Ѿ����� �ƴ� ������ ������ �� �����ϴ���
	int StickLeftAxis[2] = { 0,0 };
	int StickRightAxis[2] = { 0,0 };
public:
	GamePad(int index);
	~GamePad();

	char getControllerName() { return *gamePadName; }
	void CheckGamepadEvent(SDL_Event event);
	void SetAxisDead(int deadzone);
	void SetControllerWave(int ms,int level = 1);	//Game Controller Wave Level while ms
};