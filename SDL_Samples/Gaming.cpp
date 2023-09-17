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
    soundEffect = new Sound("P_MarcoDeath_old.wav");

    return true;
}

void Gaming::CheckKeyPress()
{
    SDL_Event event;

    //컨트롤러와 조이스틱 입력처리 충돌하지 않도록
    SDL_GameController* myController;   //연결된 컨트롤러와 통신
    SDL_Joystick* myJoystick;           //연결된 조이스틱과 통신

    myController = SDL_GameControllerOpen(0);
    const int controllerMaxAxis = 32768;    //최대 스틱 데드값

    myJoystick = SDL_JoystickOpen(0);
    const int joystickFixAxis = 256;    //스틱 미입력시 256이 지정되버리는것을 방지
    
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
            case SDL_SCANCODE_F4:       SDL_Log("F4\n");
                break;
            case SDL_SCANCODE_W:        SDL_Log("W\n");
                break;
            case SDL_SCANCODE_S:        SDL_Log("S\n");
                break;
            case SDL_SCANCODE_A:        SDL_Log("A\n");
                break;
            case SDL_SCANCODE_D:        SDL_Log("D\n");
                break;
            case SDL_SCANCODE_ESCAPE:   SDL_Log("Escape\n");
                break;
            }

        //마우스 입력
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
        case SDL_MOUSEMOTION: SDL_Log("Mouse : (%d, %d)\n", event.motion.x, event.motion.y);
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

        //컨트롤러 입력(콘솔)
        case SDL_CONTROLLERBUTTONDOWN:
            if (myController)
                switch (event.cbutton.button)
                {
                case SDL_CONTROLLER_BUTTON_A:   SDL_Log("Button A\n");
                    break;
                case SDL_CONTROLLER_BUTTON_B:   SDL_Log("Button B\n");
                    break;
                case SDL_CONTROLLER_BUTTON_X:   SDL_Log("Button X\n");
                    break;
                case SDL_CONTROLLER_BUTTON_Y:   SDL_Log("Button Y\n");
                    break;
                case SDL_CONTROLLER_BUTTON_LEFTSHOULDER:    SDL_Log("Left Button\n");
                    break;
                case SDL_CONTROLLER_BUTTON_RIGHTSHOULDER:   SDL_Log("Right Button\n");
                    break;
                case SDL_CONTROLLER_BUTTON_LEFTSTICK:   SDL_Log("Left Stick\n");
                    break;
                case SDL_CONTROLLER_BUTTON_RIGHTSTICK:  SDL_Log("Right Stick\n");
                    break;
                case SDL_CONTROLLER_BUTTON_DPAD_UP:     SDL_Log("DPAD UP\n");
                    break;
                case SDL_CONTROLLER_BUTTON_DPAD_DOWN:   SDL_Log("DPAD DOWN\n");
                    break;
                case SDL_CONTROLLER_BUTTON_DPAD_LEFT:   SDL_Log("DPAD LEFT\n");
                    break;
                case SDL_CONTROLLER_BUTTON_DPAD_RIGHT:  SDL_Log("DPAD RIGHT\n");
                    break;
                case SDL_CONTROLLER_BUTTON_START:       SDL_Log("Start Button\n");
                    break;
                case SDL_CONTROLLER_BUTTON_BACK:        SDL_Log("Back Button\n");
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

        //조이스틱 입력(아케이드)
        case SDL_JOYBUTTONDOWN:
            if (myJoystick)
                for (int i = 0; i < 12; i++)
                    if (SDL_JoystickGetButton(myJoystick, i))
                           SDL_Log("Joystick Button %d\n", i);
            break;
        case SDL_JOYHATMOTION:
            if (myJoystick)
            {
                if (SDL_JoystickGetHat(myJoystick, 0) == SDL_HAT_UP)        SDL_Log("Hat Up\n");
                else if (SDL_JoystickGetHat(myJoystick, 0) == SDL_HAT_DOWN) SDL_Log("Hat Down\n");
                
                if (SDL_JoystickGetHat(myJoystick, 0) == SDL_HAT_LEFT)      SDL_Log("Hat Left\n");
                else if (SDL_JoystickGetHat(myJoystick, 0) == SDL_HAT_RIGHT)SDL_Log("Hat Right\n");
            }
            break;
        case SDL_JOYAXISMOTION:
            if (myJoystick)
            {
                if (SDL_JoystickGetAxis(myJoystick, 0) < -joystickFixAxis)   SDL_Log("Joystick Left\n");
                else if (SDL_JoystickGetAxis(myJoystick, 0) >  joystickFixAxis)   SDL_Log("Joystick Right\n");
                
                if (SDL_JoystickGetAxis(myJoystick, 1) < -joystickFixAxis)   SDL_Log("Joystick Up\n");
                else if (SDL_JoystickGetAxis(myJoystick, 1) >  joystickFixAxis)   SDL_Log("Joystick Down\n");
            }
            break;
        }
}

void Gaming::DrawScreen()   //실제 화면에 스프라이트 및 이미지를 그리는 메서드
{

    SDL_RenderClear(renderer);  //화면 초기화
    SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);   //화면을 색상으로 채우기
    
    //이미지 그리기
    bgImg->SetColorHide(0, 0, 255);
    bgImg->Drawing(30, 50, 0);
    SDL_RenderPresent(renderer);    //화면 그리기
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