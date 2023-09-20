#pragma once
#include <SDL.h>

class Joystick
{
private:
	SDL_Joystick* myJoystick;           //����� ���̽�ƽ�� ���
	const int joystickFixAxis = 256;    //��ƽ ���Է½� 256�� �����ǹ����°��� ����
public:
	Joystick(int index = 0);
	~Joystick();
	void CheckJoystickEvent();
};