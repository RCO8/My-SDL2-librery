#include "Joystick.h"
#include <cmath>

Joystick::Joystick()
{
	for (int i = 0; i < SDL_NumJoysticks(); i++)
		myJoystick = SDL_JoystickOpen(i);

	if (myJoystick == NULL)
	{
		SDL_Log("Set Joystick Error!! %s\n", SDL_GetError());
		this->~Joystick();
	}
}
Joystick::~Joystick() { SDL_JoystickClose(myJoystick); }
void Joystick::CheckJoystickEvent(SDL_Event event)
{
	switch (event.type)
	{
		//각 버튼에 인덱스가 눌렀는지 참거짓으로 판별후 GetButton으로 반환
		case SDL_JOYBUTTONDOWN:
			for (int i = 0; i < SDL_NumJoysticks(); i++)
				if (i == event.jbutton.which)
					Buttons[i][event.jbutton.button] = true;
			break;
		case SDL_JOYBUTTONUP:
			for (int i = 0; i < SDL_NumJoysticks(); i++)
				if (i == event.jbutton.which)
					Buttons[i][event.jbutton.button] = false;
			break;
		case SDL_JOYAXISMOTION:
			for (int i = 0; i < SDL_NumJoysticks(); i++)
				if (i == event.jbutton.which)
					switch (event.jaxis.axis)//Horizontal
					{
					case 0:
						switch (event.jaxis.value)
						{
							case SDL_JOYSTICK_AXIS_MIN: AxisX[i] = -1;	break;
							case SDL_JOYSTICK_AXIS_MAX: AxisX[i] = 1;	break;
							default: AxisX[i] = 0;
						}
						break;
					case 1:
						switch (event.jaxis.value)
						{
							case SDL_JOYSTICK_AXIS_MIN: AxisY[i] = -1;	break;
							case SDL_JOYSTICK_AXIS_MAX: AxisY[i] = 1;	break;
							default: AxisY[i] = 0;
						}
						break;
					}
			break;
		case SDL_JOYHATMOTION:
			for (int i = 0; i < SDL_NumJoysticks(); i++)
				if (i == event.jbutton.which)
					switch (event.jhat.value)
					{
					case SDL_HAT_CENTERED:
						HatSwitches[i] = 0; break;
					case SDL_HAT_UP:
						HatSwitches[i] = 1; break;
					case SDL_HAT_RIGHTUP:
						HatSwitches[i] = 2; break;
					case SDL_HAT_RIGHT:
						HatSwitches[i] = 3; break;
					case SDL_HAT_RIGHTDOWN:
						HatSwitches[i] = 4; break;
					case SDL_HAT_DOWN:
						HatSwitches[i] = 5; break;
					case SDL_HAT_LEFTDOWN:
						HatSwitches[i] = 6; break;
					case SDL_HAT_LEFT:
						HatSwitches[i] = 7; break;
					case SDL_HAT_LEFTUP:
						HatSwitches[i] = 8; break;
					}
			break;
		case SDL_JOYDEVICEADDED:
			//조이스틱이 추가 연결될 시 인덱스 증가
			//maxJoystickIndex보다 초과시 연결 거부
		case SDL_JOYDEVICEREMOVED:
			//인덱스 감소 만약에 중간값이라면 앞으로 당기도록
			//그리고 인덱스가 하나라면 그대로 소멸자 호출
			break;
		//Extention Device
		case SDL_JOYBATTERYUPDATED:	//Checking Battery If Device has Wiress Connect
			SDL_Log("Battery");
			break;
		case SDL_JOYBALLMOTION:
			SDL_Log("Track Ball");
			break;
	}
}

GamePad::GamePad(int index)
{
	gameController = SDL_GameControllerOpen(index);
	if (gameController == NULL)
	{
		SDL_Log("Set Gamepad Error!! %s\n", SDL_GetError());
		this->~GamePad();
		return;
	}
	SDL_Log("Controller Connected \nName is %s", SDL_GameControllerName(gameController));
}
GamePad::~GamePad() { SDL_GameControllerClose(gameController); }

void GamePad::CheckGamepadEvent(SDL_Event event)
{
	switch (event.type)
	{
		case SDL_CONTROLLERDEVICEREMAPPED:
			switch (event.cdevice.type)
			{
			case SDL_CONTROLLER_TYPE_NINTENDO_SWITCH_PRO:
				SDL_Log("Nintendo Switch Pro");
				break;
			case SDL_CONTROLLER_TYPE_NINTENDO_SWITCH_JOYCON_LEFT:
				break;
			case SDL_CONTROLLER_TYPE_NINTENDO_SWITCH_JOYCON_RIGHT:
				break;
			case SDL_CONTROLLER_TYPE_PS3:
			case SDL_CONTROLLER_TYPE_PS4:
			case SDL_CONTROLLER_TYPE_PS5:
				break;
			case SDL_CONTROLLER_TYPE_XBOX360:
			case SDL_CONTROLLER_TYPE_XBOXONE:
				break;
			case SDL_CONTROLLER_TYPE_UNKNOWN:
				break;
			}
			break;

		case SDL_CONTROLLERBUTTONDOWN:
			switch (event.cbutton.button)
			{
				case SDL_CONTROLLER_BUTTON_A:	SDL_Log("Button A");
					break;
				case SDL_CONTROLLER_BUTTON_B:	SDL_Log("Button B");
					break;
				case SDL_CONTROLLER_BUTTON_X:	SDL_Log("Button X");
					break;
				case SDL_CONTROLLER_BUTTON_Y:	SDL_Log("Button Y");
					break;
				case SDL_CONTROLLER_BUTTON_BACK:			SDL_Log("Back");
					break;
				case SDL_CONTROLLER_BUTTON_START:			SDL_Log("Start");
					break;
				case SDL_CONTROLLER_BUTTON_LEFTSTICK:		SDL_Log("Left Stick");
					break;
				case SDL_CONTROLLER_BUTTON_RIGHTSTICK:		SDL_Log("Right Stick");
					break;
				case SDL_CONTROLLER_BUTTON_LEFTSHOULDER:	SDL_Log("Left Button");
					break;
				case SDL_CONTROLLER_BUTTON_RIGHTSHOULDER:	SDL_Log("Right Button");
					break;
				case SDL_CONTROLLER_BUTTON_DPAD_UP:			SDL_Log("DPAD UP");
					break;
				case SDL_CONTROLLER_BUTTON_DPAD_DOWN:		SDL_Log("DPAD DOWN");
					break;
				case SDL_CONTROLLER_BUTTON_DPAD_LEFT:		SDL_Log("DPAD LEFT");
					break;
				case SDL_CONTROLLER_BUTTON_DPAD_RIGHT:		SDL_Log("DPAD RIGHT");
					break;

				//extend device
				case SDL_CONTROLLER_BUTTON_TOUCHPAD:	SDL_Log("Touch Pad");
					break;
				case SDL_CONTROLLER_BUTTON_GUIDE:
				case SDL_CONTROLLER_BUTTON_INVALID:
				case SDL_CONTROLLER_BUTTON_MAX:
				case SDL_CONTROLLER_BUTTON_MISC1:
				case SDL_CONTROLLER_BUTTON_PADDLE1:
				case SDL_CONTROLLER_BUTTON_PADDLE2:
				case SDL_CONTROLLER_BUTTON_PADDLE3:
				case SDL_CONTROLLER_BUTTON_PADDLE4:
					break;
			}
			break;
		case SDL_CONTROLLERBUTTONUP:
			switch (event.cbutton.button)
			{
				//same to button down
			}
			break;
		case SDL_CONTROLLERAXISMOTION:
			switch (event.caxis.axis)
			{
				case SDL_CONTROLLER_AXIS_LEFTX:		//SDL_Log("Left X : %d", event.caxis.value);
					StickLeftAxis[0] = 1;
					if (event.caxis.value > stickDead || event.caxis.value < -stickDead)
						StickLeftAxis[0] = 2;
					if (event.caxis.value < 0)
						StickLeftAxis[0] *= -1;
					if (event.caxis.value == 0)
						StickLeftAxis[0] = 0;
					break;
				case SDL_CONTROLLER_AXIS_LEFTY:		//SDL_Log("Left Y : %d", event.caxis.value);
					StickLeftAxis[1] = 1;
					if (event.caxis.value > stickDead || event.caxis.value < -stickDead)
						StickLeftAxis[1] = 2;
					if (event.caxis.value > 0)
						StickLeftAxis[1] *= -1;
					if (event.caxis.value == -1)
						StickLeftAxis[1] = 0;
					break;
				case SDL_CONTROLLER_AXIS_RIGHTX:	//SDL_Log("Right X : %d", event.caxis.value);
					StickRightAxis[0] = 1;
					if (event.caxis.value > stickDead || event.caxis.value < -stickDead)
						StickRightAxis[0] = 2;
					if (event.caxis.value < 0)
						StickRightAxis[0] *= -1;
					if (event.caxis.value == 0)
						StickRightAxis[0] = 0;
					break;
				case SDL_CONTROLLER_AXIS_RIGHTY:	//SDL_Log("Right Y : %d", event.caxis.value);
					StickRightAxis[1] = 1;
					if (event.caxis.value > stickDead || event.caxis.value < -stickDead)
						StickRightAxis[1] = 2;
					if (event.caxis.value < 0)
						StickRightAxis[1] *= -1;
					if (event.caxis.value == -1)
						StickRightAxis[1] = 0;
					break;
				case SDL_CONTROLLER_AXIS_TRIGGERLEFT:	SDL_Log("Left Trigger : %d", event.caxis.value);
					break;
				case SDL_CONTROLLER_AXIS_TRIGGERRIGHT:	SDL_Log("Right Trigger : %d", event.caxis.value);
					break;

				//extend device
				case SDL_CONTROLLER_AXIS_INVALID:
					break;
				case SDL_CONTROLLER_AXIS_MAX:
					break;
			}
			break;

		case SDL_CONTROLLERTOUCHPADMOTION:
			SDL_Log("Touch Pad : (%d, %d)", event.ctouchpad.x, event.ctouchpad.y);
			if (event.ctouchpad.finger)
			{
				SDL_Log("Touch Pad Touch");
			}
			break;
		case SDL_CONTROLLERSENSORUPDATE:
			switch (event.csensor.sensor)
			{ 
				SDL_Log("Sensor");
			}
			break;
		case SDL_CONTROLLERDEVICEREMOVED:
			this->~GamePad();
			break;
	}
}
void GamePad::SetAxisDead(int deadzone)
{
	if (deadzone > maxAxis)
	{
		SDL_Log("Dead Zone overflow!!");
		return;
	}
	else
		stickDead = abs(deadzone);
}
void GamePad::SetControllerWave(int ms, int level)
{
	int minWave, maxWave;
	switch (level)
	{
	case 1:	//Weakest
		minWave = 1000;
		maxWave = 3000;
		break;
	case 2:	//Weak
		minWave = 5000;
		maxWave = 10000;
		break;
	case 3:	//Middle
		minWave = 15000;
		maxWave = 30000;
		break;
	case 4:	//Strong
		minWave = 50000;
		maxWave = 75000;
		break;
	case 5:	//Strongest
		minWave = 50000;
		maxWave = 100000;
		break;
	default:
		SDL_Log("Wave Level Unlimited!!");
		return;
	}
	SDL_GameControllerRumble(this->gameController, minWave, maxWave, ms);
}