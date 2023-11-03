#include "Joystick.h"

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

Joystick::~Joystick()
{
	SDL_JoystickClose(myJoystick);
}

void Joystick::CheckJoystickEvent(SDL_Event event)
{
	while (SDL_PollEvent(&event))
		switch (event.type)
		{
		case SDL_JOYBUTTONDOWN:
			switch (event.jbutton.which)	//PlayerIndex
			{
			case 0: SDL_Log("Play1"); break;
			case 1: SDL_Log("Play2"); break;
			case 2: SDL_Log("Play3"); break;
			case 3: SDL_Log("Play4"); break;
			case 4: SDL_Log("Play5"); break;
			case 5: SDL_Log("Play6"); break;
			case 6: SDL_Log("Play7"); break;
			case 7: SDL_Log("Play8"); break;
			}
			switch (event.jbutton.button)
			{
			case 0:		//SDL_Log("Button 0");
				break;
			case 1:		//SDL_Log("Button 1");
				break;
			case 2:		//SDL_Log("Button 2");
				break;
			case 3:		//SDL_Log("Button 3");
				break;
			case 4:		//SDL_Log("Button 4");
				break;
			case 5:		//SDL_Log("Button 5");
				break;
			case 6:		//SDL_Log("Button 6");
				break;
			case 7:		//SDL_Log("Button 7");
				break;
			case 8:		//SDL_Log("Button 8");
				break;
			case 9:		//SDL_Log("Button 9");
				break;
			case 10:	//SDL_Log("Button 10");
				break;
			case 11:	//SDL_Log("Button 11");
				break;
			}
			break;
		case SDL_JOYAXISMOTION:
			switch (event.jaxis.which)
			{
			case 0: SDL_Log("Play1"); break;
			case 1: SDL_Log("Play2"); break;
			case 2: SDL_Log("Play3"); break;
			case 3: SDL_Log("Play4"); break;
			case 4: SDL_Log("Play5"); break;
			case 5: SDL_Log("Play6"); break;
			case 6: SDL_Log("Play7"); break;
			case 7: SDL_Log("Play8"); break;
			}
			switch (event.jaxis.axis)
			{
			case 0:	//Horizontal
				switch (event.jaxis.value)
				{
				case SDL_JOYSTICK_AXIS_MIN:	//SDL_Log("Joystick Left");
					break;
				case SDL_JOYSTICK_AXIS_MAX:	//SDL_Log("Joystick Right");
					break;
				}
			case 1:	//Vertical
				switch (event.jaxis.value)
				{
				case SDL_JOYSTICK_AXIS_MIN:	//SDL_Log("Joystick Up");
					break;
				case SDL_JOYSTICK_AXIS_MAX:	//SDL_Log("Joystick Down");
					break;
				}
			}
			break;
		case SDL_JOYHATMOTION:
			switch (event.jhat.which)
			{
			case 0: SDL_Log("Play1"); break;
			case 1: SDL_Log("Play2"); break;
			case 2: SDL_Log("Play3"); break;
			case 3: SDL_Log("Play4"); break;
			case 4: SDL_Log("Play5"); break;
			case 5: SDL_Log("Play6"); break;
			case 6: SDL_Log("Play7"); break;
			case 7: SDL_Log("Play8"); break;
			}
			switch (event.jhat.value)
			{
			case SDL_HAT_UP:		//SDL_Log("Hat ↑");
				break;
			case SDL_HAT_LEFTUP:	//SDL_Log("Hat ↖");
				break;
			case SDL_HAT_LEFT:		//SDL_Log("Hat ←");
				break;
			case SDL_HAT_LEFTDOWN:	//SDL_Log("Hat ↙");
				break;
			case SDL_HAT_DOWN:		//SDL_Log("Hat ↓");
				break;
			case SDL_HAT_RIGHTDOWN:	//SDL_Log("Hat ↘");
				break;
			case SDL_HAT_RIGHT:		//SDL_Log("Hat →");
				break;
			case SDL_HAT_RIGHTUP:	//SDL_Log("Hat ↗");
				break;
			}
			break;
		case SDL_JOYDEVICEADDED:
			//조이스틱이 추가 연결될 시 인덱스 증가
			//maxJoystickIndex보다 초과시 연결 거부
		case SDL_JOYDEVICEREMOVED:
			//인덱스 감소 만약에 중간값이라면 앞으로 당기도록
			//그리고 인덱스가 하나라면 그대로 소멸자 호출
			if (SDL_NumJoysticks() == 1)
				this->~Joystick();
			break;
		//Extention Device
		case SDL_JOYBATTERYUPDATED:	//Checking Battery If Device has Wiress Connect
			break;
		}
}