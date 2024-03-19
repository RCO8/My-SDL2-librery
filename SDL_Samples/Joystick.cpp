#include "Joystick.h"

Joystick::Joystick()
{
	SDL_JoystickEventState(SDL_ENABLE);
	for (int i = 0; i < SDL_NumJoysticks(); i++)
	{
		myJoystick = SDL_JoystickOpen(i);
	}

	if (myJoystick == NULL)
	{
		SDL_Log("Set Joystick Error!! %s\n", SDL_GetError());
		//this->~Joystick();
	}
}
Joystick::~Joystick()
{
	SDL_JoystickClose(myJoystick);
}
void Joystick::CheckJoystickEvent(SDL_Event event)
{
	switch (event.type)
	{
		//각 버튼에 인덱스가 눌렀는지 참거짓으로 판별후 GetButton으로 반환
	case SDL_JOYBUTTONDOWN:
		for (int i = 0; i < SDL_NumJoysticks(); i++)
			if (i == event.jbutton.which)
				PlayerIndex[i].Buttons[event.jbutton.button] = true;
		break;
	case SDL_JOYBUTTONUP:
		for (int i = 0; i < SDL_NumJoysticks(); i++)
			if (i == event.jbutton.which)
				PlayerIndex[i].Buttons[event.jbutton.button] = false;
		break;
	case SDL_JOYAXISMOTION:
		for (int i = 0; i < SDL_NumJoysticks(); i++)
			if (i == event.jaxis.which)
				switch (event.jaxis.axis)//Horizontal
				{
				case 0:
					switch (event.jaxis.value)
					{
					case SDL_JOYSTICK_AXIS_MIN: 
						PlayerIndex[i].AxisX = -1; break;
					case SDL_JOYSTICK_AXIS_MAX:
						PlayerIndex[i].AxisX = 1; break;
					default:
						PlayerIndex[i].AxisX = 0;
					}
					break;
				case 1:
					switch (event.jaxis.value)
					{
					case SDL_JOYSTICK_AXIS_MIN: 
						PlayerIndex[i].AxisY = -1;	break;
					case SDL_JOYSTICK_AXIS_MAX: 
						PlayerIndex[i].AxisY = 1;	break;
					default: 
						PlayerIndex[i].AxisY = 0;
					}
					break;
				}
		break;
	case SDL_JOYHATMOTION:
		for (int i = 0; i < SDL_NumJoysticks(); i++)
			if (i == event.jhat.which)
				switch (event.jhat.value)
				{
					// 중앙, 상, 좌상, 좌, 좌하, 하, 우하, 우, 우상
					case SDL_HAT_CENTERED:
						PlayerIndex[i].HatX = 0;
						PlayerIndex[i].HatY = 0;
						break;
					case SDL_HAT_UP:
						PlayerIndex[i].HatX =  0;
						PlayerIndex[i].HatY = -1;
						break;
					case SDL_HAT_LEFTUP:
						PlayerIndex[i].HatX = -1;
						PlayerIndex[i].HatY = -1;
						break;
					case SDL_HAT_LEFT:
						PlayerIndex[i].HatX = -1;
						PlayerIndex[i].HatY =  0; 
						break;
					case SDL_HAT_LEFTDOWN:
						PlayerIndex[i].HatX = -1;
						PlayerIndex[i].HatY =  1; 
						break;
					case SDL_HAT_DOWN:
						PlayerIndex[i].HatX = 0;
						PlayerIndex[i].HatY = 1; 
						break;
					case SDL_HAT_RIGHTDOWN:
						PlayerIndex[i].HatX = 1;
						PlayerIndex[i].HatY = 1; 
						break;
					case SDL_HAT_RIGHT:
						PlayerIndex[i].HatX = 1;
						PlayerIndex[i].HatY = 0; 
						break;
					case SDL_HAT_RIGHTUP:
						PlayerIndex[i].HatX =  1;
						PlayerIndex[i].HatY = -1; 
						break;
				}
		break;
		//Extention Device
	case SDL_JOYBATTERYUPDATED:	//Checking Battery If Device has Wiress Connect
		//SDL_Log("Battery");
		break;
	case SDL_JOYBALLMOTION:
		SDL_Log("Track Ball");
		break;

	case SDL_JOYDEVICEADDED:
		SDL_Log("Joystick connected at index: %d", event.jdevice.which);
		break;
	case SDL_JOYDEVICEREMOVED:
		SDL_Log("Joystick disconnected at index: %d", event.jdevice.which);
		break;
	}
}
void Joystick::CheckJoystickConnted()
{
	SDL_JoystickEventState(SDL_ENABLE);
	for (int i = 0; i < SDL_NumJoysticks(); i++)
		myJoystick = SDL_JoystickOpen(i);
}

GamePad::GamePad(int index) : yourIndex(index)
{
	gameController = SDL_GameControllerOpen(index);
	isConnect = true;
	if (gameController == NULL)
	{
		SDL_Log("Set Gamepad Error!! %s\n", SDL_GetError());
		return;
	}
	SDL_Log("Controller Connected \nName is %s", SDL_GameControllerName(gameController));

	LeftStick = { 0,0,0,0 };
	RightStick = { 0,0,0,0 };
	PadTrigger = { 0,0,0,0 };
}
GamePad::~GamePad() 
{ 
	SDL_Log("%s 컨트롤러 제거", SDL_GameControllerName(gameController));
	SDL_GameControllerClose(gameController);
}
void GamePad::CheckGamepadEvent(SDL_Event event)
{
	switch (event.type)
	{
		case SDL_CONTROLLERBUTTONDOWN:
			ButtonCheck[event.cbutton.button] = true;
			break;
		case SDL_CONTROLLERBUTTONUP:
			ButtonCheck[event.cbutton.button] = false;
			break;
		case SDL_CONTROLLERAXISMOTION:
			switch (event.caxis.axis)
			{
				case SDL_CONTROLLER_AXIS_LEFTX:		//SDL_Log("Left X : %d", event.caxis.value);
					LeftStick.xAxis = StickUpdate(LeftStick.xAxis, event.caxis.value);
					break;
				case SDL_CONTROLLER_AXIS_LEFTY:		//SDL_Log("Left Y : %d", event.caxis.value);
					LeftStick.yAxis = StickUpdate(LeftStick.yAxis, event.caxis.value, true);
					break;
				case SDL_CONTROLLER_AXIS_RIGHTX:	//SDL_Log("Right X : %d", event.caxis.value);
					RightStick.xAxis = StickUpdate(RightStick.xAxis, event.caxis.value);
					break;
				case SDL_CONTROLLER_AXIS_RIGHTY:	//SDL_Log("Right Y : %d", event.caxis.value);
					RightStick.yAxis = StickUpdate(RightStick.yAxis, event.caxis.value, true);
					break;
				case SDL_CONTROLLER_AXIS_TRIGGERLEFT:	//SDL_Log("Left Trigger : %d", event.caxis.value);
					PadTrigger.l = event.caxis.value;
					PadTrigger.deadl = event.caxis.value > triggerDead ? true : false;
					break;
				case SDL_CONTROLLER_AXIS_TRIGGERRIGHT:	//SDL_Log("Right Trigger : %d", event.caxis.value);
					PadTrigger.r = event.caxis.value;
					PadTrigger.deadr = event.caxis.value > triggerDead ? true : false;
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
		case SDL_CONTROLLERTOUCHPADDOWN:
		case SDL_CONTROLLERTOUCHPADUP:
			break;
		case SDL_CONTROLLERSENSORUPDATE:
			switch (event.csensor.sensor)
			{ 
				SDL_Log("Sensor");
			}
			break;
		case SDL_CONTROLLERDEVICEADDED:
			if(yourIndex == event.cdevice.which)
				SetDeviceConnect();
			break;
		case SDL_CONTROLLERDEVICEREMOVED:
			isConnect = false;
			break;
		case SDL_QUIT:
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
void GamePad::SetTriggerDead(int deadzone)
{
	if (deadzone > maxAxis)
	{
		SDL_Log("Dead Zone overflow!!");
		return;
	}
	else
		triggerDead = abs(deadzone);
}
void GamePad::SetControllerWave(unsigned int ms, int level)
{
	int minWave, maxWave;
	switch (level)
	{
	case 1:	//Weakest
		minWave = 1000;		maxWave = 3000;
		break;
	case 2:	//Weak
		minWave = 5000;		maxWave = 10000;
		break;
	case 3:	//Middle
		minWave = 15000;	maxWave = 30000;
		break;
	case 4:	//Strong
		minWave = 50000;	maxWave = 75000;
		break;
	case 5:	//Strongest
		minWave = 50000;	maxWave = 100000;
		break;
	default:
		SDL_Log("Wave Level limited!!");
		return;
	}
	SDL_GameControllerRumble(this->gameController, minWave, maxWave, ms);	//진동을 울려라
}