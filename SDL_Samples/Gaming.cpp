#include "Gaming.h"

bool Gaming::GameInit()
{
    SDL_Init(SDL_INIT_EVERYTHING);

    window = SDL_CreateWindow("SDL Sample", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);
    if (window == NULL)
    {
        SDL_Log("Failed Init Window : %s \n", SDL_GetError());
        return false;
    }
    renderer = SDL_CreateRenderer(window, -1, 0);
    if (renderer == NULL)
    {
        SDL_Log("Failed Init Renderer : %s \n", SDL_GetError());
        return false;
    }

    bgImg = new Sprite(renderer, "goblin.bmp");


    return true;
}

void Gaming::CheckKeyPress()
{
    SDL_Event event;
    SDL_GameController* myController;   //����� ��Ʈ�ѷ��� ���
    SDL_Joystick* myJoystick;           //����� ���̽�ƽ�� ���

    myController = SDL_GameControllerOpen(0);
    myJoystick = SDL_JoystickOpen(0);
    
    while (SDL_PollEvent(&event))
        switch (event.type)
        {
        case SDL_QUIT:
            quit = true;
            break;
        //Ű���� �Է�
        case SDL_KEYDOWN:
            switch (event.key.keysym.scancode)
            {
            case SDL_SCANCODE_UP:       SDL_Log("Up\n");
                break;
            case SDL_SCANCODE_DOWN:     SDL_Log("Down\n");
                break;
            case SDL_SCANCODE_LEFT:     SDL_Log("Left\n");
                break;
            case SDL_SCANCODE_RIGHT:    SDL_Log("Right\n");
                break;
            case SDL_SCANCODE_RETURN:   SDL_Log("Enter\n");
                break;
            case SDL_SCANCODE_LSHIFT:   SDL_Log("Shift\n");
                break;
            case SDL_SCANCODE_LCTRL:    SDL_Log("Ctrl\n");
                break;
            case SDL_SCANCODE_LALT:     SDL_Log("Alt\n");
                break;
            case SDL_SCANCODE_SPACE:    SDL_Log("Space\n");
                break;
            case SDL_SCANCODE_F1:       SDL_Log("F1\n");
                break;
            case SDL_SCANCODE_F2:       SDL_Log("F2\n");
                break;
            case SDL_SCANCODE_F3:       SDL_Log("F3\n");
                break;
            case SDL_SCANCODE_W:        SDL_Log("W\n");
                break;
            case SDL_SCANCODE_S:        SDL_Log("S\n");
                break;
            case SDL_SCANCODE_A:        SDL_Log("A\n");
                break;
            case SDL_SCANCODE_D:        SDL_Log("D");
                break;
            case SDL_SCANCODE_ESCAPE:   SDL_Log("Escape\n");
                break;
            }
        //���콺 �Է�
        case SDL_MOUSEBUTTONDOWN:
            switch (event.button.button)
            {
            case 1: SDL_Log("Left Mouse\n");
                break;
            case 2: SDL_Log("Middle Mouse\n");
                break;
            case 3: SDL_Log("Right Mouse\n");
                break;
            }
            break;
        case SDL_MOUSEMOTION:
            SDL_Log("Mouse : (%d, %d)\n", event.motion.x, event.motion.y);
            if (event.button.button == 1)
            {
                x = event.motion.x - 16;
                y = event.motion.y - 16;
            }
            break;
        case SDL_MOUSEWHEEL:
            switch (event.wheel.y)
            {
            case 1:     SDL_Log("Wheel Up\n");
                break;
            case -1:    SDL_Log("Wheel Down\n");
                break;
            }
            break;
        //��Ʈ�ѷ� �Է�
        case SDL_CONTROLLERBUTTONDOWN:
            if (myController != NULL)
            {
                if (SDL_GameControllerGetButton(myController, SDL_CONTROLLER_BUTTON_A)) SDL_Log("Button A\n");
                if (SDL_GameControllerGetButton(myController, SDL_CONTROLLER_BUTTON_B)) SDL_Log("Button B\n");
                if (SDL_GameControllerGetButton(myController, SDL_CONTROLLER_BUTTON_X)) SDL_Log("Button X\n");
                if (SDL_GameControllerGetButton(myController, SDL_CONTROLLER_BUTTON_Y)) SDL_Log("Button Y\n");
                if (SDL_GameControllerGetButton(myController, SDL_CONTROLLER_BUTTON_LEFTSHOULDER)) SDL_Log("Left Button\n");
                if (SDL_GameControllerGetButton(myController, SDL_CONTROLLER_BUTTON_RIGHTSHOULDER)) SDL_Log("Right Button\n");
                if (SDL_GameControllerGetButton(myController, SDL_CONTROLLER_BUTTON_LEFTSTICK)) SDL_Log("Left Stick\n");
                if (SDL_GameControllerGetButton(myController, SDL_CONTROLLER_BUTTON_RIGHTSTICK)) SDL_Log("Right Stick\n");
                if (SDL_GameControllerGetButton(myController, SDL_CONTROLLER_BUTTON_DPAD_UP)) SDL_Log("DPAD UP\n");
                if (SDL_GameControllerGetButton(myController, SDL_CONTROLLER_BUTTON_DPAD_DOWN)) SDL_Log("DPAD DOWN\n");
                if (SDL_GameControllerGetButton(myController, SDL_CONTROLLER_BUTTON_DPAD_LEFT)) SDL_Log("DPAD LEFT\n");
                if (SDL_GameControllerGetButton(myController, SDL_CONTROLLER_BUTTON_DPAD_RIGHT)) SDL_Log("DPAD RIGHT\n");
                if (SDL_GameControllerGetButton(myController, SDL_CONTROLLER_BUTTON_START)) SDL_Log("Start Button\n");
                if (SDL_GameControllerGetButton(myController, SDL_CONTROLLER_BUTTON_BACK)) SDL_Log("Back Button\n");
            }
            break;
        case SDL_CONTROLLERAXISMOTION:
            if (myController != NULL)
            {
                if (SDL_GameControllerGetAxis(myController, SDL_CONTROLLER_AXIS_LEFTX))
                    SDL_Log("Left Axis X: %f\n", SDL_GameControllerGetAxis(myController, SDL_CONTROLLER_AXIS_LEFTX));
                if (SDL_GameControllerGetAxis(myController, SDL_CONTROLLER_AXIS_LEFTY))
                    SDL_Log("Left Axis Y: %f\n", SDL_GameControllerGetAxis(myController, SDL_CONTROLLER_AXIS_LEFTY));
                if (SDL_GameControllerGetAxis(myController, SDL_CONTROLLER_AXIS_RIGHTX))
                    SDL_Log("Right Axis X: %f\n", SDL_GameControllerGetAxis(myController, SDL_CONTROLLER_AXIS_RIGHTX));
                if (SDL_GameControllerGetAxis(myController, SDL_CONTROLLER_AXIS_RIGHTY))
                    SDL_Log("Right Axis Y: %f\n", SDL_GameControllerGetAxis(myController, SDL_CONTROLLER_AXIS_RIGHTY));
                if (SDL_GameControllerGetAxis(myController, SDL_CONTROLLER_AXIS_TRIGGERLEFT))
                    SDL_Log("Left Trigger: %f\n", SDL_GameControllerGetAxis(myController, SDL_CONTROLLER_AXIS_TRIGGERLEFT));
                if (SDL_GameControllerGetAxis(myController, SDL_CONTROLLER_AXIS_TRIGGERRIGHT))
                    SDL_Log("Right Trigger: %f\n", SDL_GameControllerGetAxis(myController, SDL_CONTROLLER_AXIS_TRIGGERRIGHT));
            }
            break;
        case SDL_JOYSTICK_TYPE_ARCADE_PAD:
            break;
        case SDL_JOYSTICK_TYPE_ARCADE_STICK:
            break;
        default:
            break;
        }
}

void Gaming::DrawScreen()   //���� ȭ�鿡 ��������Ʈ �� �̹����� �׸��� �޼���
{

    SDL_RenderClear(renderer);  //ȭ�� �ʱ�ȭ
    SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);   //ȭ���� �������� ä���

    bgImg->SetColorHide(0, 0, 0);
    bgImg->Drawing(x,y,0);   //�̹��� �׸���

    SDL_RenderPresent(renderer);    //ȭ�� �׸���
}

void Gaming::PlayAudio()
{

}

void Gaming::GameRun()
{
    while (!quit)
    {
        CheckKeyPress();
        DrawScreen();
        PlayAudio();
    }
}

void Gaming::GameOff()
{
    SDL_GameControllerClose(0);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
