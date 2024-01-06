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
	bool Buttons[8][12];	//���̽�ƽ ��ư ��������
	float PressedBtnTime[8][12];	//���̽�ƽ ��ư�� ������ �ð�
public:
	Joystick();
	~Joystick();
	void CheckJoystickEvent(SDL_Event event);
	//���� ����̽����� ������ ���� �Ű� ��ȯ
	int GetAxisX(int idx) const { return AxisX[idx]; }
	int GetAxisY(int idx) const { return AxisY[idx]; }
	int GetHatSwitches(int idx) const { return HatSwitches[idx]; }
	bool GetButtons(int idx, int btn) const { return Buttons[idx][btn]; }
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
	float checkBattery;

	//��ȯ�� ���̳� �Է°��� ������ �Ӽ���
	struct StickAxis
	{
		int x, y;	//�Ϲ����� �Է°�
		int deadx, deady;	//������ ����� �� (������ 2, �������� �Է��� 1, �̵����� 0)
	};
	StickAxis LeftStick = { 0,0,0,0 };
	StickAxis RightStick = { 0,0,0,0 };

	struct TriggerAxis
	{
		int l, r;
		bool deadl, deadr;
	};
	TriggerAxis PadTrigger = { 0,0,0,0 };

	bool ButtonCheck[15];
public:
	GamePad(int index);
	~GamePad();

	char getControllerName() { return *gamePadName; }
	void CheckGamepadEvent(SDL_Event event);
	void SetControllerWave(int ms, int level = 1);	//Game Controller Wave Level while ms
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