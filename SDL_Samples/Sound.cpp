#include "Sound.h"
#include <cstring>
#include <SDL_audio.h>

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

	int success = SDL_QueueAudio(dev, wav_buffer, wav_length);
	if (success != 0)
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
	SDL_PauseAudioDevice(dev, 0);	//사운드 한번만 재생
	SDL_Delay(2000);	//2초간 대기
	SDL_CloseAudioDevice(dev);	//대기 후 사운드 해제
}

void Sound::Pause()
{
	SDL_PauseAudioDevice(dev, 1);
}
void Sound::Stop()
{

}
void Sound::SetVolume() 
{
	
}