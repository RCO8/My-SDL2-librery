#include "Joystick.h"

Joystick::Joystick()
{
	int joystickIndex = SDL_NumJoysticks();
	
	for (int i = 0; i < joystickIndex; i++)
	{
		if(SDL_IsGameController(i))
			myJoystick = SDL_JoystickOpen(0);
	}

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

void Joystick::CheckJoystickEvent()
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
		switch (event.type)
		{
		case SDL_JOYBUTTONDOWN:
			switch (event.jbutton.button)
			{
			case 0:		SDL_Log("Button 0\n");
				break;
			case 1:		//SDL_Log("Button 1\n");
				break;
			case 2:		//SDL_Log("Button 2\n");
				break;
			case 3:		//SDL_Log("Button 3\n");
				break;
			case 4:		//SDL_Log("Button 4\n");
				break;
			case 5:		//SDL_Log("Button 5\n");
				break;
			case 6:		//SDL_Log("Button 6\n");
				break;
			case 7:		//SDL_Log("Button 7\n");
				break;
			case 8:		//SDL_Log("Button 8\n");
				break;
			case 9:		//SDL_Log("Button 9\n");
				break;
			case 10:	//SDL_Log("Button 10\n");
				break;
			case 11:	//SDL_Log("Button 11\n");
				break;
			}
			break;
		case SDL_JOYAXISMOTION:
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
			case SDL_HAT_UP:		//SDL_Log("Hat ¡è\n");
				break;
			case SDL_HAT_LEFTUP:	//SDL_Log("Hat ¢Ø\n");
				break;
			case SDL_HAT_LEFT:		//SDL_Log("Hat ¡ç\n");
				break;
			case SDL_HAT_LEFTDOWN:	//SDL_Log("Hat ¢×\n");
				break;
			case SDL_HAT_DOWN:		//SDL_Log("Hat ¡é\n");
				break;
			case SDL_HAT_RIGHTDOWN:	//SDL_Log("Hat ¢Ù\n");
				break;
			case SDL_HAT_RIGHT:		//SDL_Log("Hat ¡æ\n");
				break;
			case SDL_HAT_RIGHTUP:	//SDL_Log("Hat ¢Ö\n");
				break;
			}
		}
}