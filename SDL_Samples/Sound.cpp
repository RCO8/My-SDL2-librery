#include "Sound.h"

Sound::Sound(const char* filename)
{
	//사운드 불러오기 및 생성
	if (SDL_LoadWAV(filename, &wav_spec, &wav_buffer, &wav_length) == NULL)
	{
		SDL_Log("Failed to load WAV file : %s\n", SDL_GetError());
		this->~Sound();
	}
	dev = SDL_OpenAudioDevice(NULL, 0, &wav_spec, NULL, 0);
	if (dev == NULL)
	{
		SDL_Log("Failed to open audio device: %s\n", SDL_GetError());
		this->~Sound();
	}

	recallAudio = SDL_QueueAudio(dev, wav_buffer, wav_length);
	if (recallAudio != 0)
	{
		SDL_Log("Failed to queue audio: %s\n", SDL_GetError());
		this->~Sound();
	}
}

Sound::~Sound()
{
	//사운드 제거
	SDL_CloseAudioDevice(dev);
	SDL_FreeWAV(wav_buffer);
}

void Sound::Play()
{
	//소리가 재생상태가 아니라면 실행
	recallAudio = SDL_QueueAudio(dev, wav_buffer, wav_length);
	SDL_PauseAudioDevice(dev, 0);	//사운드 한번만 재생
}

void Sound::Pause()
{
	SDL_PauseAudioDevice(dev, 1);
}
void Sound::Stop()
{

}
void Sound::SetInputMode(int reStart)
{
	//입력을 받을 때 다시 재생할 것인가 아님 재생이 끝나면 할 것인가
}