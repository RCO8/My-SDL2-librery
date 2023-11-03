#include "Gaming.h"

const int windowWidth = 640;
const int windowHeight = 480;

bool Gaming::GameInit()
{
    SDL_Init(SDL_INIT_EVERYTHING);

    window = SDL_CreateWindow("Window", SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight, SDL_WINDOW_SHOWN);
    if (window == NULL)
    {
        SDL_Log("Failed Init Window : %s \n", SDL_GetError());
        return false;
    }
    renderer = SDL_CreateRenderer(window, -1, 0);
    if (renderer == NULL)
    {
        SDL_Log("Failed Init Renderer : %s", SDL_GetError());
        return false;
    }

    //Resouce Setting
    SDL_Color bgImgColor = { 34,177,76 };
    bgImg = new Sprite(renderer, "blue_bobby.bmp");
    bgImg->SetColorHide(bgImgColor);
    bgImg->SetSpriteClip(0, 0, 32, 32);
    bgImg->SetRotatePoint(bgImg->GetClipWidth() / 2, bgImg->GetClipHeight() / 2);

    buttonInterface = new Button(renderer);
    buttonInterface->SetBackgroundColor(255, 255, 0, 25);
    buttonInterface->SetOverMouseColor(0, 255, 0, 25);
    buttonInterface->SetClickColor(0, 255, 255);
    buttonInterface->SetFontDistance(5, 5, 5, 5);
    buttonInterface->SetUIText("abc");

    toggleInterface = new Toggle(renderer);
    toggleInterface->SetBackgroundColor(0, 255, 255);
    toggleInterface->SetOverMouseColor(0, 0, 255);
    toggleInterface->SetClickColor(255, 0, 255);
    toggleInterface->SetUIText("Toggle Test");

    //joystick = new Joystick();
    return true;
}

void Gaming::CheckKeyPress()
{
    const int controllerMaxAxis = 32768;    //Controller Max Axis
    SDL_GameController* myController = NULL;   //is Controller Check

    while (SDL_PollEvent(&event))
        switch (event.type)
        {
            case SDL_QUIT: quit = true; break;
            case SDL_WINDOWEVENT:
                switch (event.window.event)
                {
                case SDL_WINDOWEVENT_MINIMIZED: //SDL_Log("Window Minimize");
                    break;
                case SDL_WINDOWEVENT_ENTER:     //SDL_Log("Window Inside");
                    break;
                case SDL_WINDOWEVENT_LEAVE:     //SDL_Log("Window Outside");
                    break;
                case SDL_WINDOWEVENT_MOVED:     //SDL_Log("Window : (%d, %d)", event.window.data1, event.window.data2 - 31);  //이동된 창을 좌표로 얻기
                    break;
                case SDL_WINDOWEVENT_FOCUS_GAINED:  //SDL_Log("Window Enable");
                    break;
                case SDL_WINDOWEVENT_FOCUS_LOST:    //SDL_Log("Window Disable");
                    break;
                case SDL_WINDOWEVENT_CLOSE: quit = true; break;
                }

            //Keyboard Check
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
            case SDL_KEYUP:
                switch (event.key.keysym.scancode)  //Same to SDL_KEYDOWN
                { }
                break;

            //Mouse Check
            case SDL_MOUSEBUTTONDOWN:
                switch (event.button.button)
                {
                case 1: //SDL_Log("Left Mouse");
                    buttonInterface->ClickMouseAction(event);
                    toggleInterface->ClickMouseAction(event);
                    break;
                case 2: //SDL_Log("Middle Mouse");
                    break;
                case 3: //SDL_Log("Right Mouse");
                    break;
                }
            case SDL_MOUSEBUTTONUP:
                switch (event.button.button) //Same to SDL_MOUSEBUTTONDOWN
                {
                case 1:
                    buttonInterface->ClickMouseAction(event);
                    toggleInterface->ClickMouseAction(event);
                    break;
                case 2:
                case 3:
                    break;
                }
            case SDL_MOUSEMOTION: //SDL_Log("Mouse : (%d, %d)", event.motion.x, event.motion.y);
                buttonInterface->OverMouseAction(event.motion.x, event.motion.y);
                toggleInterface->OverMouseAction(event.motion.x, event.motion.y);
                break;
            case SDL_MOUSEWHEEL:
                switch (event.wheel.y)
                {
                case 1:     //SDL_Log("Wheel Up");
                    break;
                case -1:    //SDL_Log("Wheel Down");
                    break;
                }

            //Controller Check (Console version)
            case SDL_CONTROLLERDEVICEADDED: //if Controller is connected
                myController = SDL_GameControllerOpen(0);
                SDL_Log("Controller Connected \nName is %s", SDL_GameControllerName(myController));
                break;
            if (myController) {
            case SDL_CONTROLLERBUTTONDOWN:
                switch (event.cbutton.button)
                {
                    case SDL_CONTROLLER_BUTTON_A:   //SDL_Log("Button A");
                        break;
                    case SDL_CONTROLLER_BUTTON_B:   //SDL_Log("Button B");
                        break;
                    case SDL_CONTROLLER_BUTTON_X:   //SDL_Log("Button X");
                        break;
                    case SDL_CONTROLLER_BUTTON_Y:   //SDL_Log("Button Y");
                        break;
                    case SDL_CONTROLLER_BUTTON_LEFTSHOULDER:    //SDL_Log("Left Button");
                        break;
                    case SDL_CONTROLLER_BUTTON_RIGHTSHOULDER:   //SDL_Log("Right Button");
                        break;
                    case SDL_CONTROLLER_BUTTON_LEFTSTICK:   //SDL_Log("Left Stick");
                        break;
                    case SDL_CONTROLLER_BUTTON_RIGHTSTICK:  //SDL_Log("Right Stick");
                        break;
                    case SDL_CONTROLLER_BUTTON_DPAD_UP:     //SDL_Log("DPAD UP");
                        break;
                    case SDL_CONTROLLER_BUTTON_DPAD_DOWN:   //SDL_Log("DPAD DOWN");
                        break;
                    case SDL_CONTROLLER_BUTTON_DPAD_LEFT:   //SDL_Log("DPAD LEFT");
                        break;
                    case SDL_CONTROLLER_BUTTON_DPAD_RIGHT:  //SDL_Log("DPAD RIGHT");
                        break;
                    case SDL_CONTROLLER_BUTTON_START:       //SDL_Log("Start Button");
                        break;
                    case SDL_CONTROLLER_BUTTON_BACK:        //SDL_Log("Back Button");
                        break;
                }
                break;
            case SDL_CONTROLLERAXISMOTION:
                switch (event.caxis.axis)
                {
                    case SDL_CONTROLLER_AXIS_LEFTX:     //SDL_Log("Left Axis X: %d", event.caxis.value);
                        break;
                    case SDL_CONTROLLER_AXIS_LEFTY:     //SDL_Log("Left Axis Y: %d", event.caxis.value);
                        break;
                    case SDL_CONTROLLER_AXIS_RIGHTX:    //SDL_Log("Right Axis X: %d", event.caxis.value);
                        break;
                    case SDL_CONTROLLER_AXIS_RIGHTY:    //SDL_Log("Right Axis Y: %d", event.caxis.value);
                        break;
                    case SDL_CONTROLLER_AXIS_TRIGGERLEFT:   //SDL_Log("Left Trigger: %d", event.caxis.value);
                        break;
                    case SDL_CONTROLLER_AXIS_TRIGGERRIGHT:  //SDL_Log("Right Trigger: %d", event.caxis.value);
                        break;
                }
                break;
            case SDL_CONTROLLERDEVICEREMOVED:   //if Controller is disconnected
                SDL_Log("Controller Removed");
                SDL_GameControllerClose(0);
                break;
            }
        }
}
void Gaming::UpdateData()
{
    //게임 내 변형된 데이터를 여기에 갱신
    //만약에 이벤트에 적용을 하지 않는다면
    //mTimer.StartCount();
}
void Gaming::DrawScreen()   //Drawing Sprite or UI in this Screen
{
    SDL_SetRenderDrawColor(renderer, 0x00, 0x64, 0x00, 255);
    SDL_RenderClear(renderer);  //Screen Clear   //Fill Color in Screen
    
    //Draw Image
    bgImg->Drawing(x, y, 0);

    //Draw UI
    buttonInterface->DrawUI(30, 80, 100, 50);
    toggleInterface->DrawUI(30, 150, 20);

    SDL_RenderPresent(renderer);    //Redraw at Screen
}

void Gaming::GameRun()
{
    while (!quit)
    {
        CheckKeyPress();
        UpdateData();
        DrawScreen();
    }
}

void Gaming::GameOff()
{
    SDL_GameControllerClose(0);
    SDL_DestroyWindow(window);
    SDL_Quit();
}