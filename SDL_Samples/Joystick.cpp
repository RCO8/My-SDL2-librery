#include "Joystick.h"

Joystick::Joystick(int index = 0)
{
	myJoystick = SDL_JoystickOpen(index);
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
			case 0: SDL_Log("Button 0\n");
				break;
			case 1: SDL_Log("Button 1\n");
				break;
			case 2: SDL_Log("Button 2\n");
				break;
			case 3: SDL_Log("Button 3\n");
				break;
			case 4: SDL_Log("Button 4\n");
				break;
			case 5: SDL_Log("Button 5\n");
				break;
			case 6: SDL_Log("Button 6\n");
				break;
			case 7: SDL_Log("Button 7\n");
				break;
			case 8: SDL_Log("Button 8\n");
				break;
			case 9: SDL_Log("Button 9\n");
				break;
			case 10: SDL_Log("Button 10\n");
				break;
			case 11: SDL_Log("Button 11\n");
				break;
			}
			break;
		case SDL_JOYAXISMOTION:
			if (SDL_JoystickGetAxis(myJoystick, 0) < -joystickFixAxis)   SDL_Log("Joystick Left\n");
			else if (SDL_JoystickGetAxis(myJoystick, 0) > joystickFixAxis)   SDL_Log("Joystick Right\n");

			if (SDL_JoystickGetAxis(myJoystick, 1) < -joystickFixAxis)   SDL_Log("Joystick Up\n");
			else if (SDL_JoystickGetAxis(myJoystick, 1) > joystickFixAxis)   SDL_Log("Joystick Down\n");

			switch (event.jaxis.axis)
			{

			}
			break;
		case SDL_JOYHATMOTION:
			switch (event.jhat.hat)
			{
			case SDL_HAT_UP:	SDL_Log("Hat Up\n");
				break;
			case SDL_HAT_DOWN:	SDL_Log("Hat Down\n");
				break;
			case SDL_HAT_LEFT:	SDL_Log("Hat Left\n");
				break;
			case SDL_HAT_RIGHT:	SDL_Log("Hat Right\n");
				break;
			}
			break;
		}
}