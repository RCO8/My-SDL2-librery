#pragma once
#include <SDL.h>

const int maxJoystickIndex = 8;

class Joystick
{
private:
	SDL_Joystick* myJoystick;           //����� ���̽�ƽ�� ���
	char* joystickName;					//���� ���̽�ƽ ����̽� �̸�

	/*���� ���̽�ƽ�� �����̶�� ���͸� üũ �ʿ�*/
	float checkBattery[8];
public:
	Joystick();
	~Joystick();
	void CheckJoystickEvent(SDL_Event event);
};