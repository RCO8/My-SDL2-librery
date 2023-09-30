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
    surface = SDL_GetWindowSurface(window);
    if (surface == NULL)
    {
        SDL_Log("Failed Init Surface : %s \n", SDL_GetError());
        return false;
    }

    

    bgImg = new Sprite(renderer, "goblin.bmp");
    bgImg->SetColorHide(0, 0, 255);
    soundEffect = new Sound("P_MarcoDeath_old.wav");
    //mJoystick = new Joystick();
    return true;
}

void Gaming::CheckKeyPress()
{
    char PlayerIndex;

    const int controllerMaxAxis = 32768;    //최대 스틱 데드값
    SDL_GameController* myController = NULL;   //연결된 컨트롤러와 통신

    int joystickIndex = SDL_NumJoysticks();

    for (int i = 0; i < joystickIndex; i++)
    {
        if (SDL_IsGameController(i))
        {
            myController = SDL_GameControllerOpen(i);
        }
    }

    while (SDL_PollEvent(&event))
        switch (event.type)
        {
        case SDL_QUIT:
            quit = true;
            break;
        //키보드 입력
        case SDL_KEYDOWN:
            switch (event.key.keysym.scancode)
            {
            case SDL_SCANCODE_UP:       //SDL_Log("Up");
                break;
            case SDL_SCANCODE_DOWN:     //SDL_Log("Down");
                break;
            case SDL_SCANCODE_LEFT:     //SDL_Log("Left");
                break;
            case SDL_SCANCODE_RIGHT:    //SDL_Log("Right");
                break;
            case SDL_SCANCODE_RETURN:   //SDL_Log("Enter");
                break;
            case SDL_SCANCODE_SPACE:    //SDL_Log("Space");
                break;
            case SDL_SCANCODE_LSHIFT:   //SDL_Log("Shift");
                break;
            case SDL_SCANCODE_LCTRL:    //SDL_Log("Ctrl");
                break;
            case SDL_SCANCODE_LALT:     //SDL_Log("Alt");
                break;
            case SDL_SCANCODE_F1:       //SDL_Log("F1");
                break;
            case SDL_SCANCODE_W:        //SDL_Log("W");
                break;
            case SDL_SCANCODE_S:        //SDL_Log("S");
                break;
            case SDL_SCANCODE_A:        //SDL_Log("A");
                break;
            case SDL_SCANCODE_D:        //SDL_Log("D");
                break;
            case SDL_SCANCODE_ESCAPE:   //SDL_Log("Escape");
                break;
            }
            break;
        case SDL_KEYUP:
            switch (event.key.keysym.scancode)
            {
                //KEYDOWN 이벤트와 똑같음
            }
            break;

        //마우스 입력
        case SDL_MOUSEBUTTONDOWN:
            switch (event.button.button)
            {
            case 1: //SDL_Log("Left Mouse\n");
                break;
            case 2: //SDL_Log("Middle Mouse\n");
                break;
            case 3: //SDL_Log("Right Mouse\n");
                soundEffect->Play();
                break;
            }
            break;
        case SDL_MOUSEBUTTONUP:
            switch (event.button.button) //BUTTONDOWN 이벤트와 똑같음
            break;
        case SDL_MOUSEMOTION: //SDL_Log("Mouse : (%d, %d)\n", event.motion.x, event.motion.y);
            if (event.button.button == 1)
            {
                x = event.motion.x - 16;
                y = event.motion.y - 16;
            }
            break;
        case SDL_MOUSEWHEEL:
            switch (event.wheel.y)
            {
            case 1:     //SDL_Log("Wheel Up\n");
                break;
            case -1:    //SDL_Log("Wheel Down\n");
                break;
            }
            break;

        //컨트롤러 입력(콘솔)
        case SDL_CONTROLLERBUTTONDOWN:
                switch (event.cbutton.button)
                {
                case SDL_CONTROLLER_BUTTON_A:   //SDL_Log("%c Button A\n", PlayerIndex);
                    break;
                case SDL_CONTROLLER_BUTTON_B:   //SDL_Log("Button B\n");
                    break;
                case SDL_CONTROLLER_BUTTON_X:   //SDL_Log("Button X\n");
                    break;
                case SDL_CONTROLLER_BUTTON_Y:   //SDL_Log("Button Y\n");
                    break;
                case SDL_CONTROLLER_BUTTON_LEFTSHOULDER:    //SDL_Log("Left Button\n");
                    break;
                case SDL_CONTROLLER_BUTTON_RIGHTSHOULDER:   //SDL_Log("Right Button\n");
                    break;
                case SDL_CONTROLLER_BUTTON_LEFTSTICK:   //SDL_Log("Left Stick\n");
                    break;
                case SDL_CONTROLLER_BUTTON_RIGHTSTICK:  //SDL_Log("Right Stick\n");
                    break;
                case SDL_CONTROLLER_BUTTON_DPAD_UP:     //SDL_Log("DPAD UP\n");
                    break;
                case SDL_CONTROLLER_BUTTON_DPAD_DOWN:   //SDL_Log("DPAD DOWN\n");
                    break;
                case SDL_CONTROLLER_BUTTON_DPAD_LEFT:   //SDL_Log("DPAD LEFT\n");
                    break;
                case SDL_CONTROLLER_BUTTON_DPAD_RIGHT:  //SDL_Log("DPAD RIGHT\n");
                    break;
                case SDL_CONTROLLER_BUTTON_START:       //SDL_Log("Start Button\n");
                    break;
                case SDL_CONTROLLER_BUTTON_BACK:        //SDL_Log("Back Button\n");
                    break;
                }
            break;
        case SDL_CONTROLLERAXISMOTION:
            if (myController)
                switch (event.caxis.axis)
                {
                case SDL_CONTROLLER_AXIS_LEFTX:
                    SDL_Log("Left Axis X: %d\n", SDL_GameControllerGetAxis(myController, SDL_CONTROLLER_AXIS_LEFTX));
                    break;
                case SDL_CONTROLLER_AXIS_LEFTY:
                    SDL_Log("Left Axis Y: %d\n", SDL_GameControllerGetAxis(myController, SDL_CONTROLLER_AXIS_LEFTY));
                    break;
                case SDL_CONTROLLER_AXIS_RIGHTX:
                    SDL_Log("Right Axis X: %d\n", SDL_GameControllerGetAxis(myController, SDL_CONTROLLER_AXIS_RIGHTX));
                    break;
                case SDL_CONTROLLER_AXIS_RIGHTY:
                    SDL_Log("Right Axis Y: %d\n", SDL_GameControllerGetAxis(myController, SDL_CONTROLLER_AXIS_RIGHTY));
                    break;
                case SDL_CONTROLLER_AXIS_TRIGGERLEFT:
                    SDL_Log("Left Trigger: %d\n", SDL_GameControllerGetAxis(myController, SDL_CONTROLLER_AXIS_TRIGGERLEFT));
                    break;
                case SDL_CONTROLLER_AXIS_TRIGGERRIGHT:
                    SDL_Log("Right Trigger: %d\n", SDL_GameControllerGetAxis(myController, SDL_CONTROLLER_AXIS_TRIGGERRIGHT));
                    break;
                }
            break;
        }
}

void Gaming::DrawScreen()   //실제 화면에 스프라이트 및 이미지를 그리는 메서드
{
    SDL_RenderClear(renderer);  //화면 초기화
    SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);   //화면을 색상으로 채우기
    
    //이미지 그리기
    bgImg->SetSpriteClip(0, 0, 32, 32);
    bgImg->Drawing(x, y, 0);

    SDL_RenderPresent(renderer);    //화면 그리기
}

void Gaming::PlayAudio()
{
    //mTimer.StartCount();
}

void Gaming::GameRun()
{
    while (!quit)
    {
        CheckKeyPress();
        //mJoystick->CheckJoystickEvent();
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