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
	CheckInput GetInput(int idx) 
	{
		return PlayerIndex[idx]; 
	}

	void CheckJoystickConnted();	//���̽�ƽ ���� ����
};

//Console ver
//Single Device in class

class GamePad
{
private:
	SDL_GameController* gameController;
	char* gamePadName;
	int yourIndex;
	bool isConnect;

	const int maxAxis = 32768;    //Controller Max Axis
	int stickDead = 10000;
	int triggerDead = 10000;

	//��ȯ�� ���̳� �Է°��� ������ �Ӽ���
	struct AnalogUpdate
	{
		int analogValue;	//�Ϲ����� �Է°�
		int deadZone;		//������ ����� �� (������ 2, �������� �Է��� 1, �̵����� 0)
	};
	struct StickAxis
	{
		AnalogUpdate xAxis;
		AnalogUpdate yAxis;
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
	//���� ���� ����
	bool GetConnectState() { return isConnect; }
private:
	//��Ʈ�ѷ� ������ ��������� �翬�� ��û
	void SetDeviceConnect() 
	{
		SDL_Log("����̽� ���� %d", yourIndex + 1);
		gameController = SDL_GameControllerOpen(yourIndex); 
		isConnect = true;
	}
	AnalogUpdate StickUpdate(AnalogUpdate update, Sint16 origin, bool x = false)
	{
		int nowAxis = x ? 0 : -1;

		update.analogValue = origin;
		//������ üũ
		update.deadZone = 1;
		if (SDL_abs(origin) > stickDead) update.deadZone = 2;
		if (origin < 0)update.deadZone *= -1;
		if (origin == nowAxis)update.deadZone = 0;

		return update;
	}
};