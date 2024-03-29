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
	//이 속성들은 Gaming같은 클래스에 상호작용을 하기 위해서 값으로 반환
	struct CheckInput
	{
		int AxisX, AxisY;
		int HatX, HatY;
		bool Buttons[12];	//조이스틱 버튼 눌렀는지
	} PlayerIndex[8];
public:
	Joystick();
	~Joystick();
	void CheckJoystickEvent(SDL_Event event);
	//현재 디바이스에서 동작한 값을 매겨 반환
	CheckInput GetInput(int idx) 
	{
		return PlayerIndex[idx]; 
	}

	void CheckJoystickConnted();	//조이스틱 연결 여부
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

	//반환될 축이나 입력값을 저장할 속성들
	struct AnalogUpdate
	{
		int analogValue;	//일반적인 입력값
		int deadZone;		//데드존 통과한 값 (넘으면 2, 넘지않은 입력은 1, 미동작은 0)
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
	void SetAxisDead(int deadzone);	//스틱 데드존 설정
	void SetTriggerDead(int deadzone);	//트리거 데드존 설정

	//아날로그 스틱 받을 값
	StickAxis GetLeftAxis() const { return LeftStick; }
	StickAxis GetRightAxis() const { return RightStick; }
	//트리거 입력받을 값
	TriggerAxis GetTriggerAxis() const { return PadTrigger; }
	//버튼 동작을 받을 메서드 (단 파라미터를 SDL_CONTROLLER_BUTTON_...이런식으로 넣어야 함)
	bool GetButtonCheck(SDL_GameControllerButton btn) { return ButtonCheck[btn]; }
	//현재 연결 상태
	bool GetConnectState() { return isConnect; }
private:
	//컨트롤러 연결이 끊어질경우 재연결 요청
	void SetDeviceConnect() 
	{
		SDL_Log("디바이스 연결 %d", yourIndex + 1);
		gameController = SDL_GameControllerOpen(yourIndex); 
		isConnect = true;
	}
	AnalogUpdate StickUpdate(AnalogUpdate update, Sint16 origin, bool x = false)
	{
		int nowAxis = x ? 0 : -1;

		update.analogValue = origin;
		//데드존 체크
		update.deadZone = 1;
		if (SDL_abs(origin) > stickDead) update.deadZone = 2;
		if (origin < 0)update.deadZone *= -1;
		if (origin == nowAxis)update.deadZone = 0;

		return update;
	}
};