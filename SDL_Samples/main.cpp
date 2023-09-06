#include <SDL.h>
#include <iostream>
using namespace std;

bool quit = false;

void CheckKeyPress()
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
            if(event.key.keysym.scancode == SDL_SCANCODE_0)
                cout << (char)SDL_GetKeyFromScancode(SDL_SCANCODE_0) << endl;
            if(event.key.keysym.scancode == SDL_SCANCODE_W)
                cout << (char)SDL_GetKeyFromScancode(SDL_SCANCODE_W) << endl;
            if (event.key.keysym.scancode == SDL_SCANCODE_S)
                cout << (char)SDL_GetKeyFromScancode(SDL_SCANCODE_S) << endl;
            if (event.key.keysym.scancode == SDL_SCANCODE_A)
                cout << (char)SDL_GetKeyFromScancode(SDL_SCANCODE_A) << endl;
            if (event.key.keysym.scancode == SDL_SCANCODE_D)
                cout << (char)SDL_GetKeyFromScancode(SDL_SCANCODE_D) << endl;
            if (event.key.keysym.scancode == SDL_SCANCODE_RETURN)
                cout << "Enter" << endl;
            if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
            {
                cout << "Escape" << endl;
                quit = true;
            }
            break;
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

void DrawScreen()
{

}

int main(int argc, char** argv)
{
    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Window* window = SDL_CreateWindow("SDL Sample", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

    while (!quit)
    {
        CheckKeyPress();
        DrawScreen();

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);
    }
    SDL_GameControllerClose(0);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
	return 0;
}
