#include <SDL.h>
#include <iostream>
using namespace std;

class Gaming
{
private:
    bool quit = false;
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Texture* realScreen;
public:
    bool GameInit();
    void GameRun();
    void GameOff();
private:
    void CheckKeyPress();	//키 및 이벤트 확인
    void DrawScreen();		//배경화면 그리기
    void DrawImage();		//이미지 및 스프라이트 그리기
    void DrawParticle();	//파티클 그리기
    void PlaySound();		//소리 재생
};

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

void Gaming::DrawScreen()
{
    SDL_Surface* loadBMP = SDL_LoadBMP("img.bmp");
    if (loadBMP == NULL)
    {
        cout << "BMP not exist : %s" << SDL_GetError() << endl;
        quit = true;
    }
    realScreen = SDL_CreateTextureFromSurface(renderer, loadBMP);  //화면에 나타낼 텍스쳐 BMP를 배경화면으로

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);   //화면을 색상으로 채우기
    SDL_RenderClear(renderer);  //화면 초기화
    SDL_RenderCopy(renderer, realScreen, NULL, NULL);   //텍스쳐 그리기
    SDL_RenderPresent(renderer);    //화면 그리기
}

void Gaming::DrawImage()
{

}

void Gaming::DrawParticle()
{

}

void Gaming::PlaySound()
{
    SDL_AudioSpec wav_spec;
    Uint8* wav_buffer;
    Uint32* wav_length;
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
    SDL_DestroyTexture(realScreen);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

int main(int argc, char** argv)
{
    Gaming isGaming;
    bool gameOK = isGaming.GameInit();
    isGaming.GameRun();
    isGaming.GameOff();
	return 0;
}
