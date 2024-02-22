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
	struct CheckInput
	{
		int AxisX, AxisY;
		int HatX, HatY;
		bool Buttons[12];	//���̽�ƽ ��ư ��������
	} PlayerIndex[8];
public:
	Joystick();
	~Joystick();
	void CheckJoystickEvent(SDL_Event event);
	//���� ����̽����� ������ ���� �Ű� ��ȯ
	CheckInput GetInput(int idx) const { return PlayerIndex[idx]; }
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
	int triggerDead = 10000;

	//��ȯ�� ���̳� �Է°��� ������ �Ӽ���
	struct StickAxis
	{
		int x, y;	//�Ϲ����� �Է°�
		int deadx, deady;	//������ ����� �� (������ 2, �������� �Է��� 1, �̵����� 0)
	}LeftStick, RightStick;

	struct TriggerAxis
	{
		int l, r;
		bool deadl, deadr;
	}PadTrigger;

	bool ButtonCheck[15];
public:
	GamePad(int index);
	~GamePad();

	char getControllerName() { return *gamePadName; }
	void CheckGamepadEvent(SDL_Event event);
	void SetControllerWave(unsigned int ms, int level = 1);	//Game Controller Wave Level while ms
	void SetAxisDead(int deadzone);	//��ƽ ������ ����
	void SetTriggerDead(int deadzone);	//Ʈ���� ������ ����

	//�Ƴ��α� ��ƽ ���� ��
	StickAxis GetLeftAxis() const { return LeftStick; }
	StickAxis GetRightAxis() const { return RightStick; }
	//Ʈ���� �Է¹��� ��
	TriggerAxis GetTriggerAxis() const { return PadTrigger; }
	//��ư ������ ���� �޼��� (�� �Ķ���͸� SDL_CONTROLLER_BUTTON_...�̷������� �־�� ��)
	bool GetButtonCheck(SDL_GameControllerButton btn) { return ButtonCheck[btn]; }
};