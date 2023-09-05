#include <SDL.h>

SDL_Window* mWindow;
SDL_Renderer* mRenderer;
bool mIsRunning = true;
int mPaddleDir = 0;
const int thickness = 15;
const float paddleH = 100.0f;

Uint32 mTicksCount;
struct Vector2
{
	float x, y;
}mPaddlePos, mBallPos, mBallVel;

bool Initialize()
{
	int sdlResult = SDL_Init(SDL_INIT_VIDEO);
	if (sdlResult != 0)
	{
		SDL_Log("Unable to initialize SDL : %s", SDL_GetError());
		return false;
	}

	mWindow = SDL_CreateWindow("SDL Games", 100, 100, 1024, 768, 0);
	if (!mWindow)
	{
		SDL_Log("Failed to create window : %s", SDL_GetError());
		return false;
	}

	mRenderer = SDL_CreateRenderer(
		mWindow, -1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!mRenderer)
	{
		SDL_Log("Failed to create Renderer : %s", SDL_GetError());
		return false;
	}

	mPaddlePos.x = 10.0f;
	mPaddlePos.y = 768.0f / 2.0f;
	mBallPos.x = 1024.f / 2.f;
	mBallPos.y = 768.f / 2.f;
	mBallVel.x = -200.f;
	mBallVel.y = 235.f;

	return true;
}

void ProcessInput()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			mIsRunning = false;
			break;
		}
	}

	const Uint8* state = SDL_GetKeyboardState(NULL);
	if (state[SDL_SCANCODE_ESCAPE])
	{
		mIsRunning = false;
	}

	mPaddleDir = 0;
	if (state[SDL_SCANCODE_W])
		mPaddleDir -= 1;
	if (state[SDL_SCANCODE_S])
		mPaddleDir += 1;
}

void UpdateGame()
{
	while(!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16));

	float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;
	if (deltaTime > 0.05f)
		deltaTime = 0.05f;
	mTicksCount = SDL_GetTicks();

	if (mPaddleDir != 0)
	{
		mPaddlePos.y += mPaddleDir * 300.f * deltaTime;

		if (mPaddlePos.y < (paddleH / 2.f + thickness))
			mPaddlePos.y = paddleH / 2.f + thickness;
		else if (mPaddlePos.y > (768.f - paddleH / 2.f - thickness))
			mPaddlePos.y = 768.f - paddleH / 2.f - thickness;
	}

	mBallPos.x += mBallVel.x * deltaTime;
	mBallPos.y += mBallVel.y * deltaTime;

	float diff = mPaddlePos.y - mBallPos.y;
	diff = (diff > 0.0f) ? diff : -diff;

	if (diff <= paddleH / 2.0f && mBallPos.x <= 25.0f && mBallPos.x >= 20.0f &&
		mBallVel.x < 0.0f)
		mBallVel.x *= -1.0f;
	else if (mBallPos.x <= 0.f)
		mIsRunning = false;
	else if (mBallPos.x >= (1024.f - thickness) && mBallVel.x > 0.0f)
		mBallVel.x *= -1.f;

	if (mBallPos.y <= thickness && mBallVel.y < 0.0f)
		mBallVel.y *= -1;
	else if (mBallPos.y >= (768.f - thickness) && mBallVel.y > 0.f)
		mBallVel.y *= -1;
}

void GenerateOutput()
{

	SDL_SetRenderDrawColor(mRenderer, 0, 0, 255, 255);
	SDL_RenderClear(mRenderer);

	SDL_SetRenderDrawColor(mRenderer, 0, 255, 0, 255);
	SDL_Rect wall{
		0,0,1024,thickness
	};
	SDL_RenderFillRect(mRenderer, &wall);

	wall.y = 768 - thickness;
	SDL_RenderFillRect(mRenderer, &wall);

	wall.x = 1024 - thickness;
	wall.y = 0;
	wall.w = thickness;
	wall.h = 1024;
	SDL_RenderFillRect(mRenderer, &wall);

	SDL_Rect paddle{
		static_cast<int>(mPaddlePos.x),
		static_cast<int>(mPaddlePos.y - paddleH / 2),
		thickness,static_cast<int>(paddleH)
	};
	SDL_RenderFillRect(mRenderer, &paddle);

	SDL_Rect ball{
		static_cast<int>(mBallPos.x - thickness / 2),
		static_cast<int>(mBallPos.y - thickness / 2),
		thickness,thickness
	};
	SDL_RenderFillRect(mRenderer, &ball);
	SDL_RenderPresent(mRenderer);
}

void RunLoop()
{
	while (mIsRunning)
	{
		ProcessInput();
		UpdateGame();
		GenerateOutput();
	}
}

void Shutdown()
{
	SDL_DestroyRenderer(mRenderer);
	SDL_DestroyWindow(mWindow);
	SDL_Quit();
}

int main(int argc, char* argv[])
{

    bool success = Initialize();
	if (success)
	{
		RunLoop();
	}
	Shutdown();
    return 0;
}
