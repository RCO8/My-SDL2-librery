#include "Gaming.h"

bool Gaming::GameInit()
{
    SDL_Init(SDL_INIT_EVERYTHING);

    window = SDL_CreateWindow("SDL Sample", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);
    if (window == NULL)
    {
        cout << "Failed Init Window : %s" << SDL_GetError() << endl;
        return false;
    }
    renderer = SDL_CreateRenderer(window, -1, 0);
    if (renderer == NULL)
    {
        cout << "Failed Init Renderer : %s" << SDL_GetError() << endl;
        return false;
    }
    return true;
}

void Gaming::CheckKeyPress()
{
    SDL_Event event;
    SDL_GameController* myController;   //연결된 조이스틱과 통신
    myController = SDL_GameControllerOpen(0);

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
            case SDL_SCANCODE_UP:
                cout << "Up" << endl;
                break;
            case SDL_SCANCODE_DOWN:
                cout << "Down" << endl;
                break;
            case SDL_SCANCODE_LEFT:
                cout << "Left" << endl;
                break;
            case SDL_SCANCODE_RIGHT:
                cout << "Right" << endl;
                break;
            case SDL_SCANCODE_RETURN:
                cout << "Enter" << endl;
                break;
            case SDL_SCANCODE_LSHIFT:
                cout << "Shift" << endl;
                break;
            case SDL_SCANCODE_LCTRL:
                cout << "Ctrl" << endl;
                break;
            case SDL_SCANCODE_LALT:
                cout << "Alt" << endl;
                break;
            case SDL_SCANCODE_SPACE:
                cout << "Space" << endl;
                break;
            case SDL_SCANCODE_W:
                cout << (char)SDL_GetKeyFromScancode(SDL_SCANCODE_W) << endl;
                break;
            case SDL_SCANCODE_S:
                cout << (char)SDL_GetKeyFromScancode(SDL_SCANCODE_S) << endl;
                break;
            case SDL_SCANCODE_A:
                cout << (char)SDL_GetKeyFromScancode(SDL_SCANCODE_A) << endl;
                break;
            case SDL_SCANCODE_D:
                cout << (char)SDL_GetKeyFromScancode(SDL_SCANCODE_D) << endl;
                break;
            case SDL_SCANCODE_ESCAPE:
                cout << "Escape" << endl;
                break;
            }
            //마우스 입력
        case SDL_MOUSEBUTTONDOWN:
            switch (event.button.button)
            {
            case 1:
                cout << "Left Mouse" << endl;
                break;
            case 2:
                cout << "Middle Mouse" << endl;
                break;
            case 3:
                cout << "Right Mouse" << endl;
                break;
            }
            break;
        case SDL_MOUSEMOTION:
            cout << "Mouse moved: (" << event.motion.x << ", " << event.motion.y << ")" << endl;
            break;
        case SDL_MOUSEWHEEL:
            if (event.wheel.y > 0) cout << "Wheel Up" << endl;
            if (event.wheel.y < 0) cout << "Wheel Down" << endl;
            break;
            //컨트롤러 입력
        case SDL_CONTROLLERBUTTONDOWN:
            if (myController != NULL)
            {
                if (SDL_GameControllerGetButton(myController, SDL_CONTROLLER_BUTTON_A)) cout << "Button A" << endl;
                if (SDL_GameControllerGetButton(myController, SDL_CONTROLLER_BUTTON_B)) cout << "Button B" << endl;
                if (SDL_GameControllerGetButton(myController, SDL_CONTROLLER_BUTTON_X)) cout << "Button X" << endl;
                if (SDL_GameControllerGetButton(myController, SDL_CONTROLLER_BUTTON_Y)) cout << "Button Y" << endl;
                if (SDL_GameControllerGetButton(myController, SDL_CONTROLLER_BUTTON_LEFTSHOULDER)) cout << "Left Button" << endl;
                if (SDL_GameControllerGetButton(myController, SDL_CONTROLLER_BUTTON_RIGHTSHOULDER)) cout << "Right Button" << endl;
                if (SDL_GameControllerGetButton(myController, SDL_CONTROLLER_BUTTON_LEFTSTICK)) cout << "Left Stick" << endl;
                if (SDL_GameControllerGetButton(myController, SDL_CONTROLLER_BUTTON_RIGHTSTICK)) cout << "Right Stick" << endl;
                if (SDL_GameControllerGetButton(myController, SDL_CONTROLLER_BUTTON_DPAD_UP)) cout << "DPAD UP" << endl;
                if (SDL_GameControllerGetButton(myController, SDL_CONTROLLER_BUTTON_DPAD_DOWN)) cout << "DPAD DOWN" << endl;
                if (SDL_GameControllerGetButton(myController, SDL_CONTROLLER_BUTTON_DPAD_LEFT)) cout << "DPAD LEFT" << endl;
                if (SDL_GameControllerGetButton(myController, SDL_CONTROLLER_BUTTON_DPAD_RIGHT)) cout << "DPAD RIGHT" << endl;
                if (SDL_GameControllerGetButton(myController, SDL_CONTROLLER_BUTTON_START)) cout << "Start Button" << endl;
                if (SDL_GameControllerGetButton(myController, SDL_CONTROLLER_BUTTON_BACK)) cout << "Back Button" << endl;
            }
            break;
        case SDL_CONTROLLERAXISMOTION:
            if (myController != NULL)
            {
                if (SDL_GameControllerGetAxis(myController, SDL_CONTROLLER_AXIS_LEFTX))
                    cout << "Left Axis X: " << SDL_GameControllerGetAxis(myController, SDL_CONTROLLER_AXIS_LEFTX) << endl;
                if (SDL_GameControllerGetAxis(myController, SDL_CONTROLLER_AXIS_LEFTY))
                    cout << "Left Axis Y: " << SDL_GameControllerGetAxis(myController, SDL_CONTROLLER_AXIS_LEFTY) << endl;
                if (SDL_GameControllerGetAxis(myController, SDL_CONTROLLER_AXIS_RIGHTX))
                    cout << "Right Axis X: " << SDL_GameControllerGetAxis(myController, SDL_CONTROLLER_AXIS_RIGHTX) << endl;
                if (SDL_GameControllerGetAxis(myController, SDL_CONTROLLER_AXIS_RIGHTY))
                    cout << "Right Axis Y: " << SDL_GameControllerGetAxis(myController, SDL_CONTROLLER_AXIS_RIGHTY) << endl;
                if (SDL_GameControllerGetAxis(myController, SDL_CONTROLLER_AXIS_TRIGGERLEFT))
                    cout << "Left Trigger: " << SDL_GameControllerGetAxis(myController, SDL_CONTROLLER_AXIS_TRIGGERLEFT) << endl;
                if (SDL_GameControllerGetAxis(myController, SDL_CONTROLLER_AXIS_TRIGGERRIGHT))
                    cout << "Right Trigger: " << SDL_GameControllerGetAxis(myController, SDL_CONTROLLER_AXIS_TRIGGERRIGHT) << endl;
            }
            break;
        default:
            break;
        }
}

void Gaming::DrawScreen()
{
    SDL_RenderClear(renderer);  //화면 초기화
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);   //화면을 색상으로 채우기
    SDL_RenderPresent(renderer);    //화면 그리기
}

void Gaming::GameRun()
{
    while (!quit)
    {
        CheckKeyPress();
        DrawScreen();
    }
}

void Gaming::GameOff()
{
    SDL_GameControllerClose(0);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
