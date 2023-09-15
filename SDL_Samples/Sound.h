#pragma once
#include <SDL.h>

class Sound
{
private:
	char* fileName;	//파일 이름
	float nowVolume;

	SDL_AudioSpec wav_spec;
	SDL_AudioDeviceID dev;
	Uint8* wav_buffer;
	Uint32 wav_length;
public:
	bool mute = true;

	Sound();
	~Sound();
	void Play();
	void Pause();
	void Stop();
	void SetVolume();

	float GetVolume() const { return nowVolume; };
};