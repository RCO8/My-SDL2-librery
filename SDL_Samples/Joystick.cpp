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
			for (int i = 0; i < SDL_NumJoysticks(); i++)
				if (i == event.jbutton.which)
					switch (event.jbutton.button)
					{
					case 0:		//SDL_Log("Play %d Button 0", i + 1);
						break;
					case 1:		//SDL_Log("Play %d Button 1", i + 1);
						break;
					case 2:		//SDL_Log("Play %d Button 2", i + 1);
						break;
					case 3:		//SDL_Log("Play %d Button 3", i + 1);
						break;
					case 4:		//SDL_Log("Play %d Button 4", i + 1);
						break;
					case 5:		//SDL_Log("Play %d Button 5", i + 1);
						break;
					case 6:		//SDL_Log("Play %d Button 6", i + 1);
						break;
					case 7:		//SDL_Log("Play %d Button 7", i + 1);
						break;
					case 8:		//SDL_Log("Play %d Button 8", i + 1);
						break;
					case 9:		//SDL_Log("Play %d Button 9", i + 1);
						break;
					case 10:	//SDL_Log("Play %d Button 10", i + 1);
						break;
					case 11:	//SDL_Log("Play %d Button 11", i + 1);
						break;
					}
			break;
		case SDL_JOYAXISMOTION:
			for (int i = 0; i < SDL_NumJoysticks(); i++)
				if (i == event.jbutton.which)
					switch (event.jaxis.axis)
					{
					case 0:	//Horizontal
						switch (event.jaxis.value)
						{
						case SDL_JOYSTICK_AXIS_MIN:	//SDL_Log("Play %d Joystick Left", i + 1);
							break;
						case SDL_JOYSTICK_AXIS_MAX:	//SDL_Log("Play %d Joystick Right", i + 1);
							break;
						}
						break;
					case 1:	//Vertical
						switch (event.jaxis.value)
						{
						case SDL_JOYSTICK_AXIS_MIN:	//SDL_Log("Play %d Joystick Up", i + 1);
							break;
						case SDL_JOYSTICK_AXIS_MAX:	//SDL_Log("Play %d Joystick Down", i + 1);
							break;
						}
						break;
					}
			break;
		case SDL_JOYHATMOTION:
			for (int i = 0; i < SDL_NumJoysticks(); i++)
				if (i == event.jbutton.which)
					switch (event.jhat.value)
					{
					case SDL_HAT_UP:		//SDL_Log("Play %d Hat ��", i + 1);
						break;
					case SDL_HAT_LEFTUP:	//SDL_Log("Play %d Hat ��", i + 1);
						break;
					case SDL_HAT_LEFT:		//SDL_Log("Play %d Hat ��", i + 1);
						break;
					case SDL_HAT_LEFTDOWN:	//SDL_Log("Play %d Hat ��", i + 1);
						break;
					case SDL_HAT_DOWN:		//SDL_Log("Play %d Hat ��", i + 1);
						break;
					case SDL_HAT_RIGHTDOWN:	//SDL_Log("Play %d Hat ��", i + 1);
						break;
					case SDL_HAT_RIGHT:		//SDL_Log("Play %d Hat ��", i + 1);
						break;
					case SDL_HAT_RIGHTUP:	//SDL_Log("Play %d Hat ��", i + 1);
						break;
					}
			break;
		case SDL_JOYDEVICEADDED:
			//���̽�ƽ�� �߰� ����� �� �ε��� ����
			//maxJoystickIndex���� �ʰ��� ���� �ź�
			myJoystick = SDL_JoystickOpen(SDL_NumJoysticks()-1);
			SDL_Log("%d", SDL_NumJoysticks());
		case SDL_JOYDEVICEREMOVED:
			//�ε��� ���� ���࿡ �߰����̶�� ������ ��⵵��
			//�׸��� �ε����� �ϳ���� �״�� �Ҹ��� ȣ��
			SDL_Log("%d", SDL_NumJoysticks());
			if (SDL_NumJoysticks() == 1)
				this->~Joystick();
			break;
		//Extention Device
		case SDL_JOYBATTERYUPDATED:	//Checking Battery If Device has Wiress Connect
			break;
		}
}