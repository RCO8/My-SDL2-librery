#include "Joystick.h"

Joystick::Joystick()
{
	numOfJoysticks = SDL_NumJoysticks();

	myJoystick[0] = SDL_JoystickOpen(0);	//i에 따라 플레이어 번호 지정
	if (myJoystick[0] == NULL)
	{
		SDL_Log("Set Joystick Error!! %s", SDL_GetError());
		this->~Joystick();
	}
}

Joystick::~Joystick()
{
	SDL_JoystickClose(myJoystick[0]);
}

void Joystick::CheckJoystickEvent()
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
		switch (event.type)
		{
		case SDL_JOYBUTTONDOWN:
			switch (event.jbutton.button)
			{
			case 0:		SDL_Log("Button 0");
				break;
			case 1:		SDL_Log("Button 1");
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
		case SDL_JOYBUTTONUP:
			switch (event.jbutton.button)
			{
			case 0:
			case 1:
			case 2:
			case 3:
			case 4:
			case 5:
			case 6:
			case 7:
			case 8:
			case 9:
			case 10:
			case 11:
				break;
			}
			break;

		case SDL_JOYAXISMOTION:
			switch (event.jaxis.axis)
			{
			case 0:	//Horizontal
				switch (event.jaxis.value)
				{
				case SDL_JOYSTICK_AXIS_MIN:	SDL_Log("Joystick Left");
					break;
				case SDL_JOYSTICK_AXIS_MAX:	SDL_Log("Joystick Right");
					break;
				}
				break;
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
		}
}

void SetTurbo()
{

}