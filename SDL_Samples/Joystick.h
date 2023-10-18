#pragma once
#include <SDL.h>

const int maxJoystickIndex = 8;	//�ִ� ���̽�ƽ ���� ��

class Joystick
{
private:
	SDL_Joystick* myJoystick[8];           //����� ���̽�ƽ�� ���
	int numOfJoysticks;
public:
	Joystick();
	~Joystick();
	void CheckJoystickEvent();
	void SetTurbo();	//�ͺ� ����
	//������������ �ٽ� ����������
};