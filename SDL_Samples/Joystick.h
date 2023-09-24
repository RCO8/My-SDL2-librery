#pragma once
#include <SDL.h>

const int maxJoystickIndex = 8;

class Joystick
{
private:
	SDL_Joystick* myJoystick;           //����� ���̽�ƽ�� ���
	const int joystickFixAxis = 256;    //��ƽ ���Է½� 256�� �����ǹ����°��� ����
public:
	Joystick();
	~Joystick();
	void CheckJoystickEvent();
};